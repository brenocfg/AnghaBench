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
 scalar_t__ arg_type_is_mem_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ arg_type_is_mem_size (int /*<<< orphan*/ ) ; 
 scalar_t__ check_args_pair_invalid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool check_arg_pair_ok(const struct bpf_func_proto *fn)
{
	/* bpf_xxx(..., buf, len) call will access 'len'
	 * bytes from memory 'buf'. Both arg types need
	 * to be paired, so make sure there's no buggy
	 * helper function specification.
	 */
	if (arg_type_is_mem_size(fn->arg1_type) ||
	    arg_type_is_mem_ptr(fn->arg5_type)  ||
	    check_args_pair_invalid(fn->arg1_type, fn->arg2_type) ||
	    check_args_pair_invalid(fn->arg2_type, fn->arg3_type) ||
	    check_args_pair_invalid(fn->arg3_type, fn->arg4_type) ||
	    check_args_pair_invalid(fn->arg4_type, fn->arg5_type))
		return false;

	return true;
}