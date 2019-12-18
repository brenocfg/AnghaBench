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
struct strparser {int /*<<< orphan*/ * skb_head; int /*<<< orphan*/  work; int /*<<< orphan*/  msg_timer_work; int /*<<< orphan*/  stopped; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 

void strp_done(struct strparser *strp)
{
	WARN_ON(!strp->stopped);

	cancel_delayed_work_sync(&strp->msg_timer_work);
	cancel_work_sync(&strp->work);

	if (strp->skb_head) {
		kfree_skb(strp->skb_head);
		strp->skb_head = NULL;
	}
}