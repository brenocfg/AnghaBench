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
struct bpf_func_proto {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ check_arg_pair_ok (struct bpf_func_proto const*) ; 
 scalar_t__ check_raw_mode_ok (struct bpf_func_proto const*) ; 
 scalar_t__ check_refcount_ok (struct bpf_func_proto const*,int) ; 

__attribute__((used)) static int check_func_proto(const struct bpf_func_proto *fn, int func_id)
{
	return check_raw_mode_ok(fn) &&
	       check_arg_pair_ok(fn) &&
	       check_refcount_ok(fn, func_id) ? 0 : -EINVAL;
}