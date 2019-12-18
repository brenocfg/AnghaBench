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
struct btf_type {int /*<<< orphan*/  size; } ;
struct btf {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  BTF_KIND_ARRAY 132 
#define  BTF_KIND_ENUM 131 
#define  BTF_KIND_FWD 130 
#define  BTF_KIND_INT 129 
#define  BTF_KIND_PTR 128 
 int EINVAL ; 
 TYPE_1__* btf_array (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_int_bits (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_int_offset (struct btf_type const*) ; 
 scalar_t__ btf_is_composite (struct btf_type const*) ; 
 int btf_kind (struct btf_type const*) ; 
 int /*<<< orphan*/  pr_warning (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct btf_type* skip_mods_and_typedefs (struct btf const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bpf_core_fields_are_compat(const struct btf *local_btf,
				      __u32 local_id,
				      const struct btf *targ_btf,
				      __u32 targ_id)
{
	const struct btf_type *local_type, *targ_type;

recur:
	local_type = skip_mods_and_typedefs(local_btf, local_id, &local_id);
	targ_type = skip_mods_and_typedefs(targ_btf, targ_id, &targ_id);
	if (!local_type || !targ_type)
		return -EINVAL;

	if (btf_is_composite(local_type) && btf_is_composite(targ_type))
		return 1;
	if (btf_kind(local_type) != btf_kind(targ_type))
		return 0;

	switch (btf_kind(local_type)) {
	case BTF_KIND_FWD:
	case BTF_KIND_PTR:
		return 1;
	case BTF_KIND_ENUM:
		return local_type->size == targ_type->size;
	case BTF_KIND_INT:
		return btf_int_offset(local_type) == 0 &&
		       btf_int_offset(targ_type) == 0 &&
		       local_type->size == targ_type->size &&
		       btf_int_bits(local_type) == btf_int_bits(targ_type);
	case BTF_KIND_ARRAY:
		local_id = btf_array(local_type)->type;
		targ_id = btf_array(targ_type)->type;
		goto recur;
	default:
		pr_warning("unexpected kind %d relocated, local [%d], target [%d]\n",
			   btf_kind(local_type), local_id, targ_id);
		return 0;
	}
}