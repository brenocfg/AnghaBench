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
struct btf_type {scalar_t__ name_off; size_t type; } ;
struct btf_param {size_t type; } ;
struct btf_member {size_t type; } ;
struct btf_dump_type_aux_state {scalar_t__ order_state; int /*<<< orphan*/  referenced; } ;
struct btf_dump {struct btf_dump_type_aux_state* type_states; int /*<<< orphan*/  btf; } ;
typedef  size_t __u32 ;
typedef  int __u16 ;
struct TYPE_2__ {size_t type; } ;

/* Variables and functions */
#define  BTF_KIND_ARRAY 142 
#define  BTF_KIND_CONST 141 
#define  BTF_KIND_DATASEC 140 
#define  BTF_KIND_ENUM 139 
#define  BTF_KIND_FUNC 138 
#define  BTF_KIND_FUNC_PROTO 137 
#define  BTF_KIND_FWD 136 
#define  BTF_KIND_INT 135 
#define  BTF_KIND_PTR 134 
#define  BTF_KIND_RESTRICT 133 
#define  BTF_KIND_STRUCT 132 
#define  BTF_KIND_TYPEDEF 131 
#define  BTF_KIND_UNION 130 
#define  BTF_KIND_VAR 129 
#define  BTF_KIND_VOLATILE 128 
 int EINVAL ; 
 int ELOOP ; 
 scalar_t__ ORDERED ; 
 scalar_t__ ORDERING ; 
 struct btf_type* btf__type_by_id (int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__* btf_array (struct btf_type const*) ; 
 int btf_dump_add_emit_queue_id (struct btf_dump*,size_t) ; 
 scalar_t__ btf_is_composite (struct btf_type const*) ; 
 int btf_kind (struct btf_type const*) ; 
 struct btf_member* btf_members (struct btf_type const*) ; 
 struct btf_param* btf_params (struct btf_type const*) ; 
 int btf_vlen (struct btf_type const*) ; 
 int /*<<< orphan*/  pr_warning (char*,size_t) ; 

__attribute__((used)) static int btf_dump_order_type(struct btf_dump *d, __u32 id, bool through_ptr)
{
	/*
	 * Order state is used to detect strong link cycles, but only for BTF
	 * kinds that are or could be an independent definition (i.e.,
	 * stand-alone fwd decl, enum, typedef, struct, union). Ptrs, arrays,
	 * func_protos, modifiers are just means to get to these definitions.
	 * Int/void don't need definitions, they are assumed to be always
	 * properly defined.  We also ignore datasec, var, and funcs for now.
	 * So for all non-defining kinds, we never even set ordering state,
	 * for defining kinds we set ORDERING and subsequently ORDERED if it
	 * forms a strong link.
	 */
	struct btf_dump_type_aux_state *tstate = &d->type_states[id];
	const struct btf_type *t;
	__u16 vlen;
	int err, i;

	/* return true, letting typedefs know that it's ok to be emitted */
	if (tstate->order_state == ORDERED)
		return 1;

	t = btf__type_by_id(d->btf, id);

	if (tstate->order_state == ORDERING) {
		/* type loop, but resolvable through fwd declaration */
		if (btf_is_composite(t) && through_ptr && t->name_off != 0)
			return 0;
		pr_warning("unsatisfiable type cycle, id:[%u]\n", id);
		return -ELOOP;
	}

	switch (btf_kind(t)) {
	case BTF_KIND_INT:
		tstate->order_state = ORDERED;
		return 0;

	case BTF_KIND_PTR:
		err = btf_dump_order_type(d, t->type, true);
		tstate->order_state = ORDERED;
		return err;

	case BTF_KIND_ARRAY:
		return btf_dump_order_type(d, btf_array(t)->type, through_ptr);

	case BTF_KIND_STRUCT:
	case BTF_KIND_UNION: {
		const struct btf_member *m = btf_members(t);
		/*
		 * struct/union is part of strong link, only if it's embedded
		 * (so no ptr in a path) or it's anonymous (so has to be
		 * defined inline, even if declared through ptr)
		 */
		if (through_ptr && t->name_off != 0)
			return 0;

		tstate->order_state = ORDERING;

		vlen = btf_vlen(t);
		for (i = 0; i < vlen; i++, m++) {
			err = btf_dump_order_type(d, m->type, false);
			if (err < 0)
				return err;
		}

		if (t->name_off != 0) {
			err = btf_dump_add_emit_queue_id(d, id);
			if (err < 0)
				return err;
		}

		tstate->order_state = ORDERED;
		return 1;
	}
	case BTF_KIND_ENUM:
	case BTF_KIND_FWD:
		/*
		 * non-anonymous or non-referenced enums are top-level
		 * declarations and should be emitted. Same logic can be
		 * applied to FWDs, it won't hurt anyways.
		 */
		if (t->name_off != 0 || !tstate->referenced) {
			err = btf_dump_add_emit_queue_id(d, id);
			if (err)
				return err;
		}
		tstate->order_state = ORDERED;
		return 1;

	case BTF_KIND_TYPEDEF: {
		int is_strong;

		is_strong = btf_dump_order_type(d, t->type, through_ptr);
		if (is_strong < 0)
			return is_strong;

		/* typedef is similar to struct/union w.r.t. fwd-decls */
		if (through_ptr && !is_strong)
			return 0;

		/* typedef is always a named definition */
		err = btf_dump_add_emit_queue_id(d, id);
		if (err)
			return err;

		d->type_states[id].order_state = ORDERED;
		return 1;
	}
	case BTF_KIND_VOLATILE:
	case BTF_KIND_CONST:
	case BTF_KIND_RESTRICT:
		return btf_dump_order_type(d, t->type, through_ptr);

	case BTF_KIND_FUNC_PROTO: {
		const struct btf_param *p = btf_params(t);
		bool is_strong;

		err = btf_dump_order_type(d, t->type, through_ptr);
		if (err < 0)
			return err;
		is_strong = err > 0;

		vlen = btf_vlen(t);
		for (i = 0; i < vlen; i++, p++) {
			err = btf_dump_order_type(d, p->type, through_ptr);
			if (err < 0)
				return err;
			if (err > 0)
				is_strong = true;
		}
		return is_strong;
	}
	case BTF_KIND_FUNC:
	case BTF_KIND_VAR:
	case BTF_KIND_DATASEC:
		d->type_states[id].order_state = ORDERED;
		return 0;

	default:
		return -EINVAL;
	}
}