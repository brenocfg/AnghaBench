#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct id_stack {int cnt; scalar_t__ ids; } ;
struct btf_type {scalar_t__ type; } ;
struct btf_dump {int decl_stack_cnt; scalar_t__ decl_stack; int /*<<< orphan*/  btf; } ;
typedef  scalar_t__ __u32 ;
struct TYPE_2__ {scalar_t__ type; } ;

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
 TYPE_1__* btf_array (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_dump_emit_type_chain (struct btf_dump*,struct id_stack*,char const*,int) ; 
 int btf_dump_push_decl_stack_id (struct btf_dump*,scalar_t__) ; 
 int btf_kind (struct btf_type const*) ; 
 int /*<<< orphan*/  pr_warning (char*,int,...) ; 

__attribute__((used)) static void btf_dump_emit_type_decl(struct btf_dump *d, __u32 id,
				    const char *fname, int lvl)
{
	struct id_stack decl_stack;
	const struct btf_type *t;
	int err, stack_start;

	stack_start = d->decl_stack_cnt;
	for (;;) {
		err = btf_dump_push_decl_stack_id(d, id);
		if (err < 0) {
			/*
			 * if we don't have enough memory for entire type decl
			 * chain, restore stack, emit warning, and try to
			 * proceed nevertheless
			 */
			pr_warning("not enough memory for decl stack:%d", err);
			d->decl_stack_cnt = stack_start;
			return;
		}

		/* VOID */
		if (id == 0)
			break;

		t = btf__type_by_id(d->btf, id);
		switch (btf_kind(t)) {
		case BTF_KIND_PTR:
		case BTF_KIND_VOLATILE:
		case BTF_KIND_CONST:
		case BTF_KIND_RESTRICT:
		case BTF_KIND_FUNC_PROTO:
			id = t->type;
			break;
		case BTF_KIND_ARRAY:
			id = btf_array(t)->type;
			break;
		case BTF_KIND_INT:
		case BTF_KIND_ENUM:
		case BTF_KIND_FWD:
		case BTF_KIND_STRUCT:
		case BTF_KIND_UNION:
		case BTF_KIND_TYPEDEF:
			goto done;
		default:
			pr_warning("unexpected type in decl chain, kind:%u, id:[%u]\n",
				   btf_kind(t), id);
			goto done;
		}
	}
done:
	/*
	 * We might be inside a chain of declarations (e.g., array of function
	 * pointers returning anonymous (so inlined) structs, having another
	 * array field). Each of those needs its own "stack frame" to handle
	 * emitting of declarations. Those stack frames are non-overlapping
	 * portions of shared btf_dump->decl_stack. To make it a bit nicer to
	 * handle this set of nested stacks, we create a view corresponding to
	 * our own "stack frame" and work with it as an independent stack.
	 * We'll need to clean up after emit_type_chain() returns, though.
	 */
	decl_stack.ids = d->decl_stack + stack_start;
	decl_stack.cnt = d->decl_stack_cnt - stack_start;
	btf_dump_emit_type_chain(d, &decl_stack, fname, lvl);
	/*
	 * emit_type_chain() guarantees that it will pop its entire decl_stack
	 * frame before returning. But it works with a read-only view into
	 * decl_stack, so it doesn't actually pop anything from the
	 * perspective of shared btf_dump->decl_stack, per se. We need to
	 * reset decl_stack state to how it was before us to avoid it growing
	 * all the time.
	 */
	d->decl_stack_cnt = stack_start;
}