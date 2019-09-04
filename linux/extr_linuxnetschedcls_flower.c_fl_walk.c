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
struct tcf_walker {scalar_t__ (* fn ) (struct tcf_proto*,struct cls_fl_filter*,struct tcf_walker*) ;int stop; int /*<<< orphan*/  count; scalar_t__ cookie; int /*<<< orphan*/  skip; } ;
struct tcf_proto {int /*<<< orphan*/  root; } ;
struct cls_fl_head {int /*<<< orphan*/  handle_idr; } ;
struct cls_fl_filter {scalar_t__ handle; } ;

/* Variables and functions */
 struct cls_fl_filter* idr_get_next_ul (int /*<<< orphan*/ *,scalar_t__*) ; 
 struct cls_fl_head* rtnl_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct tcf_proto*,struct cls_fl_filter*,struct tcf_walker*) ; 

__attribute__((used)) static void fl_walk(struct tcf_proto *tp, struct tcf_walker *arg)
{
	struct cls_fl_head *head = rtnl_dereference(tp->root);
	struct cls_fl_filter *f;

	arg->count = arg->skip;

	while ((f = idr_get_next_ul(&head->handle_idr,
				    &arg->cookie)) != NULL) {
		if (arg->fn(tp, f, arg) < 0) {
			arg->stop = 1;
			break;
		}
		arg->cookie = f->handle + 1;
		arg->count++;
	}
}