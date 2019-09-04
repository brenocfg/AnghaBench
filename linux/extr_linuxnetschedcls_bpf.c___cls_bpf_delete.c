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
struct tcf_proto {int /*<<< orphan*/  root; } ;
struct netlink_ext_ack {int dummy; } ;
struct cls_bpf_prog {int /*<<< orphan*/  rwork; int /*<<< orphan*/  exts; int /*<<< orphan*/  res; int /*<<< orphan*/  link; int /*<<< orphan*/  handle; } ;
struct cls_bpf_head {int /*<<< orphan*/  handle_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cls_bpf_delete_prog (struct cls_bpf_prog*) ; 
 int /*<<< orphan*/  cls_bpf_delete_prog_work ; 
 int /*<<< orphan*/  cls_bpf_stop_offload (struct tcf_proto*,struct cls_bpf_prog*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 struct cls_bpf_head* rtnl_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ tcf_exts_get_net (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_unbind_filter (struct tcf_proto*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __cls_bpf_delete(struct tcf_proto *tp, struct cls_bpf_prog *prog,
			     struct netlink_ext_ack *extack)
{
	struct cls_bpf_head *head = rtnl_dereference(tp->root);

	idr_remove(&head->handle_idr, prog->handle);
	cls_bpf_stop_offload(tp, prog, extack);
	list_del_rcu(&prog->link);
	tcf_unbind_filter(tp, &prog->res);
	if (tcf_exts_get_net(&prog->exts))
		tcf_queue_work(&prog->rwork, cls_bpf_delete_prog_work);
	else
		__cls_bpf_delete_prog(prog);
}