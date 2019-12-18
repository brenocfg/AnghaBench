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
struct btf_var_secinfo {size_t type; } ;
struct btf_type {size_t type; } ;
struct btf_param {size_t type; } ;
struct btf_member {size_t type; } ;
struct btf_dump {TYPE_1__* type_states; int /*<<< orphan*/  btf; } ;
struct btf_array {size_t index_type; size_t type; } ;
typedef  int __u16 ;
struct TYPE_2__ {int referenced; } ;

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
 int btf__get_nr_types (int /*<<< orphan*/ ) ; 
 struct btf_type* btf__type_by_id (int /*<<< orphan*/ ,int) ; 
 struct btf_array* btf_array (struct btf_type const*) ; 
 int btf_kind (struct btf_type const*) ; 
 struct btf_member* btf_members (struct btf_type const*) ; 
 struct btf_param* btf_params (struct btf_type const*) ; 
 struct btf_var_secinfo* btf_var_secinfos (struct btf_type const*) ; 
 int btf_vlen (struct btf_type const*) ; 

__attribute__((used)) static int btf_dump_mark_referenced(struct btf_dump *d)
{
	int i, j, n = btf__get_nr_types(d->btf);
	const struct btf_type *t;
	__u16 vlen;

	for (i = 1; i <= n; i++) {
		t = btf__type_by_id(d->btf, i);
		vlen = btf_vlen(t);

		switch (btf_kind(t)) {
		case BTF_KIND_INT:
		case BTF_KIND_ENUM:
		case BTF_KIND_FWD:
			break;

		case BTF_KIND_VOLATILE:
		case BTF_KIND_CONST:
		case BTF_KIND_RESTRICT:
		case BTF_KIND_PTR:
		case BTF_KIND_TYPEDEF:
		case BTF_KIND_FUNC:
		case BTF_KIND_VAR:
			d->type_states[t->type].referenced = 1;
			break;

		case BTF_KIND_ARRAY: {
			const struct btf_array *a = btf_array(t);

			d->type_states[a->index_type].referenced = 1;
			d->type_states[a->type].referenced = 1;
			break;
		}
		case BTF_KIND_STRUCT:
		case BTF_KIND_UNION: {
			const struct btf_member *m = btf_members(t);

			for (j = 0; j < vlen; j++, m++)
				d->type_states[m->type].referenced = 1;
			break;
		}
		case BTF_KIND_FUNC_PROTO: {
			const struct btf_param *p = btf_params(t);

			for (j = 0; j < vlen; j++, p++)
				d->type_states[p->type].referenced = 1;
			break;
		}
		case BTF_KIND_DATASEC: {
			const struct btf_var_secinfo *v = btf_var_secinfos(t);

			for (j = 0; j < vlen; j++, v++)
				d->type_states[v->type].referenced = 1;
			break;
		}
		default:
			return -EINVAL;
		}
	}
	return 0;
}