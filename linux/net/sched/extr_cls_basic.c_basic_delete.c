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
struct basic_head {int /*<<< orphan*/  flist; int /*<<< orphan*/  handle_idr; } ;
struct basic_filter {int /*<<< orphan*/  rwork; int /*<<< orphan*/  exts; int /*<<< orphan*/  handle; int /*<<< orphan*/  res; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  basic_delete_filter_work ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 struct basic_head* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_exts_get_net (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_unbind_filter (struct tcf_proto*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int basic_delete(struct tcf_proto *tp, void *arg, bool *last,
			bool rtnl_held, struct netlink_ext_ack *extack)
{
	struct basic_head *head = rtnl_dereference(tp->root);
	struct basic_filter *f = arg;

	list_del_rcu(&f->link);
	tcf_unbind_filter(tp, &f->res);
	idr_remove(&head->handle_idr, f->handle);
	tcf_exts_get_net(&f->exts);
	tcf_queue_work(&f->rwork, basic_delete_filter_work);
	*last = list_empty(&head->flist);
	return 0;
}