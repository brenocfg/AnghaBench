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
struct ap_queue {int /*<<< orphan*/  lock; TYPE_1__* card; int /*<<< orphan*/  total_request_count; int /*<<< orphan*/  requestq_count; int /*<<< orphan*/  requestq; } ;
struct ap_message {int /*<<< orphan*/  list; int /*<<< orphan*/  receive; } ;
struct TYPE_2__ {int /*<<< orphan*/  total_request_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_EVENT_POLL ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ap_sm_event_loop (struct ap_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ap_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ap_queue_message(struct ap_queue *aq, struct ap_message *ap_msg)
{
	/* For asynchronous message handling a valid receive-callback
	 * is required.
	 */
	BUG_ON(!ap_msg->receive);

	spin_lock_bh(&aq->lock);
	/* Queue the message. */
	list_add_tail(&ap_msg->list, &aq->requestq);
	aq->requestq_count++;
	aq->total_request_count++;
	atomic_inc(&aq->card->total_request_count);
	/* Send/receive as many request from the queue as possible. */
	ap_wait(ap_sm_event_loop(aq, AP_EVENT_POLL));
	spin_unlock_bh(&aq->lock);
}