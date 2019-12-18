#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  q; } ;
struct htb_class {int /*<<< orphan*/  block; int /*<<< orphan*/  rate_est; TYPE_1__ leaf; int /*<<< orphan*/  level; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  gen_kill_estimator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct htb_class*) ; 
 int /*<<< orphan*/  qdisc_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_block_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void htb_destroy_class(struct Qdisc *sch, struct htb_class *cl)
{
	if (!cl->level) {
		WARN_ON(!cl->leaf.q);
		qdisc_put(cl->leaf.q);
	}
	gen_kill_estimator(&cl->rate_est);
	tcf_block_put(cl->block);
	kfree(cl);
}