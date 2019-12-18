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
struct rsvp_filter {int /*<<< orphan*/  rwork; int /*<<< orphan*/  exts; int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rsvp_delete_filter (struct rsvp_filter*) ; 
 int /*<<< orphan*/  rsvp_delete_filter_work ; 
 scalar_t__ tcf_exts_get_net (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_unbind_filter (struct tcf_proto*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rsvp_delete_filter(struct tcf_proto *tp, struct rsvp_filter *f)
{
	tcf_unbind_filter(tp, &f->res);
	/* all classifiers are required to call tcf_exts_destroy() after rcu
	 * grace period, since converted-to-rcu actions are relying on that
	 * in cleanup() callback
	 */
	if (tcf_exts_get_net(&f->exts))
		tcf_queue_work(&f->rwork, rsvp_delete_filter_work);
	else
		__rsvp_delete_filter(f);
}