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
struct btf_var_secinfo {int offset; int type; } ;
struct btf_type {int size; void* info; int /*<<< orphan*/  name_off; } ;
struct btf_member {int offset; int type; int /*<<< orphan*/  name_off; } ;
struct btf {int dummy; } ;
struct TYPE_2__ {int btf_datasec; int btf_func; } ;
struct bpf_object {struct btf* btf; TYPE_1__ caps; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 void* BTF_INFO_ENC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int BTF_INT_ENC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BTF_KIND_ENUM ; 
 int /*<<< orphan*/  BTF_KIND_INT ; 
 int /*<<< orphan*/  BTF_KIND_STRUCT ; 
 int /*<<< orphan*/  BTF_KIND_TYPEDEF ; 
 int btf__get_nr_types (struct btf*) ; 
 scalar_t__ btf__name_by_offset (struct btf*,int /*<<< orphan*/ ) ; 
 scalar_t__ btf__type_by_id (struct btf*,int) ; 
 scalar_t__ btf_is_datasec (struct btf_type*) ; 
 scalar_t__ btf_is_func (struct btf_type*) ; 
 scalar_t__ btf_is_func_proto (struct btf_type*) ; 
 scalar_t__ btf_is_var (struct btf_type*) ; 
 struct btf_member* btf_members (struct btf_type*) ; 
 struct btf_var_secinfo* btf_var_secinfos (struct btf_type*) ; 
 int btf_vlen (struct btf_type*) ; 

__attribute__((used)) static void bpf_object__sanitize_btf(struct bpf_object *obj)
{
	bool has_datasec = obj->caps.btf_datasec;
	bool has_func = obj->caps.btf_func;
	struct btf *btf = obj->btf;
	struct btf_type *t;
	int i, j, vlen;

	if (!obj->btf || (has_func && has_datasec))
		return;

	for (i = 1; i <= btf__get_nr_types(btf); i++) {
		t = (struct btf_type *)btf__type_by_id(btf, i);

		if (!has_datasec && btf_is_var(t)) {
			/* replace VAR with INT */
			t->info = BTF_INFO_ENC(BTF_KIND_INT, 0, 0);
			/*
			 * using size = 1 is the safest choice, 4 will be too
			 * big and cause kernel BTF validation failure if
			 * original variable took less than 4 bytes
			 */
			t->size = 1;
			*(int *)(t + 1) = BTF_INT_ENC(0, 0, 8);
		} else if (!has_datasec && btf_is_datasec(t)) {
			/* replace DATASEC with STRUCT */
			const struct btf_var_secinfo *v = btf_var_secinfos(t);
			struct btf_member *m = btf_members(t);
			struct btf_type *vt;
			char *name;

			name = (char *)btf__name_by_offset(btf, t->name_off);
			while (*name) {
				if (*name == '.')
					*name = '_';
				name++;
			}

			vlen = btf_vlen(t);
			t->info = BTF_INFO_ENC(BTF_KIND_STRUCT, 0, vlen);
			for (j = 0; j < vlen; j++, v++, m++) {
				/* order of field assignments is important */
				m->offset = v->offset * 8;
				m->type = v->type;
				/* preserve variable name as member name */
				vt = (void *)btf__type_by_id(btf, v->type);
				m->name_off = vt->name_off;
			}
		} else if (!has_func && btf_is_func_proto(t)) {
			/* replace FUNC_PROTO with ENUM */
			vlen = btf_vlen(t);
			t->info = BTF_INFO_ENC(BTF_KIND_ENUM, 0, vlen);
			t->size = sizeof(__u32); /* kernel enforced */
		} else if (!has_func && btf_is_func(t)) {
			/* replace FUNC with TYPEDEF */
			t->info = BTF_INFO_ENC(BTF_KIND_TYPEDEF, 0, 0);
		}
	}
}