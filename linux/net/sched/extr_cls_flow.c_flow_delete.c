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
struct flow_head {int /*<<< orphan*/  filters; } ;
struct flow_filter {int /*<<< orphan*/  rwork; int /*<<< orphan*/  exts; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  flow_destroy_filter_work ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 struct flow_head* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_exts_get_net (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flow_delete(struct tcf_proto *tp, void *arg, bool *last,
		       bool rtnl_held, struct netlink_ext_ack *extack)
{
	struct flow_head *head = rtnl_dereference(tp->root);
	struct flow_filter *f = arg;

	list_del_rcu(&f->list);
	tcf_exts_get_net(&f->exts);
	tcf_queue_work(&f->rwork, flow_destroy_filter_work);
	*last = list_empty(&head->filters);
	return 0;
}