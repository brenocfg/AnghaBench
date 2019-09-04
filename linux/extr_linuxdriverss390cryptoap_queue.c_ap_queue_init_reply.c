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
struct ap_queue {int /*<<< orphan*/  lock; struct ap_message* reply; } ;
struct ap_message {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_EVENT_POLL ; 
 int /*<<< orphan*/  ap_sm_event (struct ap_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ap_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ap_queue_init_reply(struct ap_queue *aq, struct ap_message *reply)
{
	aq->reply = reply;

	spin_lock_bh(&aq->lock);
	ap_wait(ap_sm_event(aq, AP_EVENT_POLL));
	spin_unlock_bh(&aq->lock);
}