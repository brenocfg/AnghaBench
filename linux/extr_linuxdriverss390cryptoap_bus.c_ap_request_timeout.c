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
struct timer_list {int dummy; } ;
struct ap_queue {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_EVENT_TIMEOUT ; 
 int /*<<< orphan*/  ap_sm_event (struct ap_queue*,int /*<<< orphan*/ ) ; 
 scalar_t__ ap_suspend_flag ; 
 int /*<<< orphan*/  ap_wait (int /*<<< orphan*/ ) ; 
 struct ap_queue* aq ; 
 struct ap_queue* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout ; 

void ap_request_timeout(struct timer_list *t)
{
	struct ap_queue *aq = from_timer(aq, t, timeout);

	if (ap_suspend_flag)
		return;
	spin_lock_bh(&aq->lock);
	ap_wait(ap_sm_event(aq, AP_EVENT_TIMEOUT));
	spin_unlock_bh(&aq->lock);
}