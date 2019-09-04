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
typedef  int /*<<< orphan*/  wait_queue_entry_t ;
typedef  int u32 ;
struct mixart_msg {int dummy; } ;
struct mixart_mgr {TYPE_1__* pci; int /*<<< orphan*/  msg_sleep; int /*<<< orphan*/  msg_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int MSG_CANCEL_NOTIFY_MASK ; 
 int /*<<< orphan*/  MSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  MSG_TIMEOUT_JIFFIES ; 
 int MSG_TYPE_MASK ; 
 int MSG_TYPE_NOTIFY ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 long schedule_timeout (int /*<<< orphan*/ ) ; 
 int send_msg (struct mixart_mgr*,struct mixart_msg*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_BUG_ON (int) ; 

int snd_mixart_send_msg_wait_notif(struct mixart_mgr *mgr,
				   struct mixart_msg *request, u32 notif_event)
{
	int err;
	wait_queue_entry_t wait;
	long timeout;

	if (snd_BUG_ON(!notif_event))
		return -EINVAL;
	if (snd_BUG_ON((notif_event & MSG_TYPE_MASK) != MSG_TYPE_NOTIFY))
		return -EINVAL;
	if (snd_BUG_ON(notif_event & MSG_CANCEL_NOTIFY_MASK))
		return -EINVAL;

	init_waitqueue_entry(&wait, current);

	mutex_lock(&mgr->msg_lock);
	/* send the message */
	err = send_msg(mgr, request, MSG_DEFAULT_SIZE, 1, &notif_event);  /* send and mark the notification event pending */
	if(err) {
		mutex_unlock(&mgr->msg_lock);
		return err;
	}

	set_current_state(TASK_UNINTERRUPTIBLE);
	add_wait_queue(&mgr->msg_sleep, &wait);
	mutex_unlock(&mgr->msg_lock);
	timeout = schedule_timeout(MSG_TIMEOUT_JIFFIES);
	remove_wait_queue(&mgr->msg_sleep, &wait);

	if (! timeout) {
		/* error - no ack */
		dev_err(&mgr->pci->dev,
			"error: notification %x not received\n", notif_event);
		return -EIO;
	}

	return 0;
}