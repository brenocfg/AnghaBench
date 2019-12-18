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
struct bpf_func_proto {int /*<<< orphan*/  arg5_type; int /*<<< orphan*/  arg4_type; int /*<<< orphan*/  arg3_type; int /*<<< orphan*/  arg2_type; int /*<<< orphan*/  arg1_type; } ;

/* Variables and functions */
 scalar_t__ arg_type_may_be_refcounted (int /*<<< orphan*/ ) ; 
 scalar_t__ is_acquire_function (int) ; 

__attribute__((used)) static bool check_refcount_ok(const struct bpf_func_proto *fn, int func_id)
{
	int count = 0;

	if (arg_type_may_be_refcounted(fn->arg1_type))
		count++;
	if (arg_type_may_be_refcounted(fn->arg2_type))
		count++;
	if (arg_type_may_be_refcounted(fn->arg3_type))
		count++;
	if (arg_type_may_be_refcounted(fn->arg4_type))
		count++;
	if (arg_type_may_be_refcounted(fn->arg5_type))
		count++;

	/* A reference acquiring function cannot acquire
	 * another refcounted ptr.
	 */
	if (is_acquire_function(func_id) && count)
		return false;

	/* We only support one arg being unreferenced at the moment,
	 * which is sufficient for the helper functions we have right now.
	 */
	return count <= 1;
}