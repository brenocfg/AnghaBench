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
struct btf_var_secinfo {scalar_t__ offset; int /*<<< orphan*/  type; } ;
struct btf_var {scalar_t__ linkage; } ;
struct btf_type {scalar_t__ size; int /*<<< orphan*/  name_off; } ;
struct btf {int dummy; } ;
struct bpf_object {int dummy; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 scalar_t__ BTF_VAR_STATIC ; 
 int EINVAL ; 
 int ENOENT ; 
 int bpf_object__section_size (struct bpf_object*,char const*,scalar_t__*) ; 
 int bpf_object__variable_offset (struct bpf_object*,char const*,scalar_t__*) ; 
 char* btf__name_by_offset (struct btf*,int /*<<< orphan*/ ) ; 
 struct btf_type* btf__type_by_id (struct btf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btf_is_var (struct btf_type const*) ; 
 struct btf_var* btf_var (struct btf_type const*) ; 
 struct btf_var_secinfo* btf_var_secinfos (struct btf_type*) ; 
 scalar_t__ btf_vlen (struct btf_type*) ; 
 int /*<<< orphan*/  compare_vsi_off ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  qsort (struct btf_type*,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btf_fixup_datasec(struct bpf_object *obj, struct btf *btf,
			     struct btf_type *t)
{
	__u32 size = 0, off = 0, i, vars = btf_vlen(t);
	const char *name = btf__name_by_offset(btf, t->name_off);
	const struct btf_type *t_var;
	struct btf_var_secinfo *vsi;
	const struct btf_var *var;
	int ret;

	if (!name) {
		pr_debug("No name found in string section for DATASEC kind.\n");
		return -ENOENT;
	}

	ret = bpf_object__section_size(obj, name, &size);
	if (ret || !size || (t->size && t->size != size)) {
		pr_debug("Invalid size for section %s: %u bytes\n", name, size);
		return -ENOENT;
	}

	t->size = size;

	for (i = 0, vsi = btf_var_secinfos(t); i < vars; i++, vsi++) {
		t_var = btf__type_by_id(btf, vsi->type);
		var = btf_var(t_var);

		if (!btf_is_var(t_var)) {
			pr_debug("Non-VAR type seen in section %s\n", name);
			return -EINVAL;
		}

		if (var->linkage == BTF_VAR_STATIC)
			continue;

		name = btf__name_by_offset(btf, t_var->name_off);
		if (!name) {
			pr_debug("No name found in string section for VAR kind\n");
			return -ENOENT;
		}

		ret = bpf_object__variable_offset(obj, name, &off);
		if (ret) {
			pr_debug("No offset found in symbol table for VAR %s\n",
				 name);
			return -ENOENT;
		}

		vsi->offset = off;
	}

	qsort(t + 1, vars, sizeof(*vsi), compare_vsi_off);
	return 0;
}