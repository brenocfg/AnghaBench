#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct id_stack {int cnt; scalar_t__* ids; } ;
struct btf_type {int /*<<< orphan*/  name_off; } ;
struct btf_param {int /*<<< orphan*/  type; int /*<<< orphan*/  name_off; } ;
struct btf_dump {int /*<<< orphan*/  btf; } ;
struct btf_array {int /*<<< orphan*/  nelems; } ;
typedef  scalar_t__ __u32 ;
typedef  int __u16 ;

/* Variables and functions */
#define  BTF_KIND_ARRAY 139 
#define  BTF_KIND_CONST 138 
#define  BTF_KIND_ENUM 137 
#define  BTF_KIND_FUNC_PROTO 136 
#define  BTF_KIND_FWD 135 
#define  BTF_KIND_INT 134 
#define  BTF_KIND_PTR 133 
#define  BTF_KIND_RESTRICT 132 
#define  BTF_KIND_STRUCT 131 
#define  BTF_KIND_TYPEDEF 130 
#define  BTF_KIND_UNION 129 
#define  BTF_KIND_VOLATILE 128 
 struct btf_type* btf__type_by_id (int /*<<< orphan*/ ,scalar_t__) ; 
 struct btf_array* btf_array (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_dump_emit_enum_def (struct btf_dump*,scalar_t__,struct btf_type const*,int) ; 
 int /*<<< orphan*/  btf_dump_emit_enum_fwd (struct btf_dump*,scalar_t__,struct btf_type const*) ; 
 int /*<<< orphan*/  btf_dump_emit_fwd_def (struct btf_dump*,scalar_t__,struct btf_type const*) ; 
 int /*<<< orphan*/  btf_dump_emit_mods (struct btf_dump*,struct id_stack*) ; 
 int /*<<< orphan*/  btf_dump_emit_name (struct btf_dump*,char const*,int) ; 
 int /*<<< orphan*/  btf_dump_emit_struct_def (struct btf_dump*,scalar_t__,struct btf_type const*,int) ; 
 int /*<<< orphan*/  btf_dump_emit_struct_fwd (struct btf_dump*,scalar_t__,struct btf_type const*) ; 
 int /*<<< orphan*/  btf_dump_emit_type_decl (struct btf_dump*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  btf_dump_ident_name (struct btf_dump*,scalar_t__) ; 
 int /*<<< orphan*/  btf_dump_printf (struct btf_dump*,char*,...) ; 
 int btf_is_array (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_is_mod (struct btf_type const*) ; 
 int btf_kind (struct btf_type const*) ; 
 char* btf_name_of (struct btf_dump*,int /*<<< orphan*/ ) ; 
 struct btf_param* btf_params (struct btf_type const*) ; 
 int btf_vlen (struct btf_type const*) ; 
 int /*<<< orphan*/  pr_warning (char*,int,scalar_t__) ; 

__attribute__((used)) static void btf_dump_emit_type_chain(struct btf_dump *d,
				     struct id_stack *decls,
				     const char *fname, int lvl)
{
	/*
	 * last_was_ptr is used to determine if we need to separate pointer
	 * asterisk (*) from previous part of type signature with space, so
	 * that we get `int ***`, instead of `int * * *`. We default to true
	 * for cases where we have single pointer in a chain. E.g., in ptr ->
	 * func_proto case. func_proto will start a new emit_type_chain call
	 * with just ptr, which should be emitted as (*) or (*<fname>), so we
	 * don't want to prepend space for that last pointer.
	 */
	bool last_was_ptr = true;
	const struct btf_type *t;
	const char *name;
	__u16 kind;
	__u32 id;

	while (decls->cnt) {
		id = decls->ids[--decls->cnt];
		if (id == 0) {
			/* VOID is a special snowflake */
			btf_dump_emit_mods(d, decls);
			btf_dump_printf(d, "void");
			last_was_ptr = false;
			continue;
		}

		t = btf__type_by_id(d->btf, id);
		kind = btf_kind(t);

		switch (kind) {
		case BTF_KIND_INT:
			btf_dump_emit_mods(d, decls);
			name = btf_name_of(d, t->name_off);
			btf_dump_printf(d, "%s", name);
			break;
		case BTF_KIND_STRUCT:
		case BTF_KIND_UNION:
			btf_dump_emit_mods(d, decls);
			/* inline anonymous struct/union */
			if (t->name_off == 0)
				btf_dump_emit_struct_def(d, id, t, lvl);
			else
				btf_dump_emit_struct_fwd(d, id, t);
			break;
		case BTF_KIND_ENUM:
			btf_dump_emit_mods(d, decls);
			/* inline anonymous enum */
			if (t->name_off == 0)
				btf_dump_emit_enum_def(d, id, t, lvl);
			else
				btf_dump_emit_enum_fwd(d, id, t);
			break;
		case BTF_KIND_FWD:
			btf_dump_emit_mods(d, decls);
			btf_dump_emit_fwd_def(d, id, t);
			break;
		case BTF_KIND_TYPEDEF:
			btf_dump_emit_mods(d, decls);
			btf_dump_printf(d, "%s", btf_dump_ident_name(d, id));
			break;
		case BTF_KIND_PTR:
			btf_dump_printf(d, "%s", last_was_ptr ? "*" : " *");
			break;
		case BTF_KIND_VOLATILE:
			btf_dump_printf(d, " volatile");
			break;
		case BTF_KIND_CONST:
			btf_dump_printf(d, " const");
			break;
		case BTF_KIND_RESTRICT:
			btf_dump_printf(d, " restrict");
			break;
		case BTF_KIND_ARRAY: {
			const struct btf_array *a = btf_array(t);
			const struct btf_type *next_t;
			__u32 next_id;
			bool multidim;
			/*
			 * GCC has a bug
			 * (https://gcc.gnu.org/bugzilla/show_bug.cgi?id=8354)
			 * which causes it to emit extra const/volatile
			 * modifiers for an array, if array's element type has
			 * const/volatile modifiers. Clang doesn't do that.
			 * In general, it doesn't seem very meaningful to have
			 * a const/volatile modifier for array, so we are
			 * going to silently skip them here.
			 */
			while (decls->cnt) {
				next_id = decls->ids[decls->cnt - 1];
				next_t = btf__type_by_id(d->btf, next_id);
				if (btf_is_mod(next_t))
					decls->cnt--;
				else
					break;
			}

			if (decls->cnt == 0) {
				btf_dump_emit_name(d, fname, last_was_ptr);
				btf_dump_printf(d, "[%u]", a->nelems);
				return;
			}

			next_id = decls->ids[decls->cnt - 1];
			next_t = btf__type_by_id(d->btf, next_id);
			multidim = btf_is_array(next_t);
			/* we need space if we have named non-pointer */
			if (fname[0] && !last_was_ptr)
				btf_dump_printf(d, " ");
			/* no parentheses for multi-dimensional array */
			if (!multidim)
				btf_dump_printf(d, "(");
			btf_dump_emit_type_chain(d, decls, fname, lvl);
			if (!multidim)
				btf_dump_printf(d, ")");
			btf_dump_printf(d, "[%u]", a->nelems);
			return;
		}
		case BTF_KIND_FUNC_PROTO: {
			const struct btf_param *p = btf_params(t);
			__u16 vlen = btf_vlen(t);
			int i;

			btf_dump_emit_mods(d, decls);
			if (decls->cnt) {
				btf_dump_printf(d, " (");
				btf_dump_emit_type_chain(d, decls, fname, lvl);
				btf_dump_printf(d, ")");
			} else {
				btf_dump_emit_name(d, fname, last_was_ptr);
			}
			btf_dump_printf(d, "(");
			/*
			 * Clang for BPF target generates func_proto with no
			 * args as a func_proto with a single void arg (e.g.,
			 * `int (*f)(void)` vs just `int (*f)()`). We are
			 * going to pretend there are no args for such case.
			 */
			if (vlen == 1 && p->type == 0) {
				btf_dump_printf(d, ")");
				return;
			}

			for (i = 0; i < vlen; i++, p++) {
				if (i > 0)
					btf_dump_printf(d, ", ");

				/* last arg of type void is vararg */
				if (i == vlen - 1 && p->type == 0) {
					btf_dump_printf(d, "...");
					break;
				}

				name = btf_name_of(d, p->name_off);
				btf_dump_emit_type_decl(d, p->type, name, lvl);
			}

			btf_dump_printf(d, ")");
			return;
		}
		default:
			pr_warning("unexpected type in decl chain, kind:%u, id:[%u]\n",
				   kind, id);
			return;
		}

		last_was_ptr = kind == BTF_KIND_PTR;
	}

	btf_dump_emit_name(d, fname, last_was_ptr);
}