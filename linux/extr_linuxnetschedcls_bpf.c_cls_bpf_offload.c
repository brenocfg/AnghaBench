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
struct tcf_proto {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct cls_bpf_prog {int /*<<< orphan*/  gen_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ cls_bpf_flags (int /*<<< orphan*/ ) ; 
 int cls_bpf_offload_cmd (struct tcf_proto*,struct cls_bpf_prog*,struct cls_bpf_prog*,struct netlink_ext_ack*) ; 
 scalar_t__ tc_skip_hw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cls_bpf_offload(struct tcf_proto *tp, struct cls_bpf_prog *prog,
			   struct cls_bpf_prog *oldprog,
			   struct netlink_ext_ack *extack)
{
	if (prog && oldprog &&
	    cls_bpf_flags(prog->gen_flags) !=
	    cls_bpf_flags(oldprog->gen_flags))
		return -EINVAL;

	if (prog && tc_skip_hw(prog->gen_flags))
		prog = NULL;
	if (oldprog && tc_skip_hw(oldprog->gen_flags))
		oldprog = NULL;
	if (!prog && !oldprog)
		return 0;

	return cls_bpf_offload_cmd(tp, prog, oldprog, extack);
}