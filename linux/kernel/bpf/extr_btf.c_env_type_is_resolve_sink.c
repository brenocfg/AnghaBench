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
struct btf_verifier_env {int resolve_mode; } ;
struct btf_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  RESOLVE_PTR 130 
#define  RESOLVE_STRUCT_OR_ARRAY 129 
#define  RESOLVE_TBD 128 
 int /*<<< orphan*/  btf_type_is_array (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_type_is_modifier (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_type_is_ptr (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_type_is_struct (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_type_needs_resolve (struct btf_type const*) ; 

__attribute__((used)) static bool env_type_is_resolve_sink(const struct btf_verifier_env *env,
				     const struct btf_type *next_type)
{
	switch (env->resolve_mode) {
	case RESOLVE_TBD:
		/* int, enum or void is a sink */
		return !btf_type_needs_resolve(next_type);
	case RESOLVE_PTR:
		/* int, enum, void, struct, array, func or func_proto is a sink
		 * for ptr
		 */
		return !btf_type_is_modifier(next_type) &&
			!btf_type_is_ptr(next_type);
	case RESOLVE_STRUCT_OR_ARRAY:
		/* int, enum, void, ptr, func or func_proto is a sink
		 * for struct and array
		 */
		return !btf_type_is_modifier(next_type) &&
			!btf_type_is_array(next_type) &&
			!btf_type_is_struct(next_type);
	default:
		BUG();
	}
}