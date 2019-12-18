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
typedef  scalar_t__ u32 ;
struct btf_verifier_env {int dummy; } ;
struct btf_type {scalar_t__ size; scalar_t__ name_off; } ;
struct btf_array {int /*<<< orphan*/  index_type; int /*<<< orphan*/  type; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BTF_TYPE_ID_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ EINVAL ; 
 struct btf_array* btf_type_array (struct btf_type const*) ; 
 scalar_t__ btf_type_kflag (struct btf_type const*) ; 
 scalar_t__ btf_type_vlen (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_verifier_log_basic (struct btf_verifier_env*,struct btf_type const*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  btf_verifier_log_type (struct btf_verifier_env*,struct btf_type const*,char*) ; 

__attribute__((used)) static s32 btf_array_check_meta(struct btf_verifier_env *env,
				const struct btf_type *t,
				u32 meta_left)
{
	const struct btf_array *array = btf_type_array(t);
	u32 meta_needed = sizeof(*array);

	if (meta_left < meta_needed) {
		btf_verifier_log_basic(env, t,
				       "meta_left:%u meta_needed:%u",
				       meta_left, meta_needed);
		return -EINVAL;
	}

	/* array type should not have a name */
	if (t->name_off) {
		btf_verifier_log_type(env, t, "Invalid name");
		return -EINVAL;
	}

	if (btf_type_vlen(t)) {
		btf_verifier_log_type(env, t, "vlen != 0");
		return -EINVAL;
	}

	if (btf_type_kflag(t)) {
		btf_verifier_log_type(env, t, "Invalid btf_info kind_flag");
		return -EINVAL;
	}

	if (t->size) {
		btf_verifier_log_type(env, t, "size != 0");
		return -EINVAL;
	}

	/* Array elem type and index type cannot be in type void,
	 * so !array->type and !array->index_type are not allowed.
	 */
	if (!array->type || !BTF_TYPE_ID_VALID(array->type)) {
		btf_verifier_log_type(env, t, "Invalid elem");
		return -EINVAL;
	}

	if (!array->index_type || !BTF_TYPE_ID_VALID(array->index_type)) {
		btf_verifier_log_type(env, t, "Invalid index");
		return -EINVAL;
	}

	btf_verifier_log_type(env, t, NULL);

	return meta_needed;
}