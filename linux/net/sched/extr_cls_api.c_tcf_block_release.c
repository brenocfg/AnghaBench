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
struct tcf_block {int dummy; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct tcf_block*) ; 
 int /*<<< orphan*/  qdisc_put (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_put_unlocked (struct Qdisc*) ; 
 int /*<<< orphan*/  tcf_block_refcnt_put (struct tcf_block*,int) ; 

__attribute__((used)) static void tcf_block_release(struct Qdisc *q, struct tcf_block *block,
			      bool rtnl_held)
{
	if (!IS_ERR_OR_NULL(block))
		tcf_block_refcnt_put(block, rtnl_held);

	if (q) {
		if (rtnl_held)
			qdisc_put(q);
		else
			qdisc_put_unlocked(q);
	}
}