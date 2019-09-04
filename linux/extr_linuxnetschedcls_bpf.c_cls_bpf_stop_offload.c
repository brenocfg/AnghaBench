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
struct cls_bpf_prog {int dummy; } ;

/* Variables and functions */
 int cls_bpf_offload_cmd (struct tcf_proto*,int /*<<< orphan*/ *,struct cls_bpf_prog*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static void cls_bpf_stop_offload(struct tcf_proto *tp,
				 struct cls_bpf_prog *prog,
				 struct netlink_ext_ack *extack)
{
	int err;

	err = cls_bpf_offload_cmd(tp, NULL, prog, extack);
	if (err)
		pr_err("Stopping hardware offload failed: %d\n", err);
}