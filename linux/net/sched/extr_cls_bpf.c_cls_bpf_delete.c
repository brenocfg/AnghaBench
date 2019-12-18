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
struct cls_bpf_head {int /*<<< orphan*/  plist; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cls_bpf_delete (struct tcf_proto*,void*,struct netlink_ext_ack*) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 struct cls_bpf_head* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cls_bpf_delete(struct tcf_proto *tp, void *arg, bool *last,
			  bool rtnl_held, struct netlink_ext_ack *extack)
{
	struct cls_bpf_head *head = rtnl_dereference(tp->root);

	__cls_bpf_delete(tp, arg, extack);
	*last = list_empty(&head->plist);
	return 0;
}