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
struct qeth_cmd_buffer {struct qeth_channel* channel; } ;
struct qeth_channel {int /*<<< orphan*/  irq_pending; int /*<<< orphan*/  ccwdev; int /*<<< orphan*/  ccw; } ;
struct qeth_card {int /*<<< orphan*/  wait_q; } ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int) ; 
 int /*<<< orphan*/  QETH_IPA_TIMEOUT ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ccw_device_start_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_prepare_control_data (struct qeth_card*,int,struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  qeth_release_buffer (struct qeth_channel*,struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qeth_osn_send_control_data(struct qeth_card *card, int len,
			   struct qeth_cmd_buffer *iob)
{
	struct qeth_channel *channel = iob->channel;
	unsigned long flags;
	int rc = 0;

	QETH_CARD_TEXT(card, 5, "osndctrd");

	wait_event(card->wait_q,
		   atomic_cmpxchg(&channel->irq_pending, 0, 1) == 0);
	qeth_prepare_control_data(card, len, iob);
	QETH_CARD_TEXT(card, 6, "osnoirqp");
	spin_lock_irqsave(get_ccwdev_lock(channel->ccwdev), flags);
	rc = ccw_device_start_timeout(channel->ccwdev, channel->ccw,
				      (addr_t) iob, 0, 0, QETH_IPA_TIMEOUT);
	spin_unlock_irqrestore(get_ccwdev_lock(channel->ccwdev), flags);
	if (rc) {
		QETH_DBF_MESSAGE(2, "qeth_osn_send_control_data: "
			   "ccw_device_start rc = %i\n", rc);
		QETH_CARD_TEXT_(card, 2, " err%d", rc);
		qeth_release_buffer(channel, iob);
		atomic_set(&channel->irq_pending, 0);
		wake_up(&card->wait_q);
	}
	return rc;
}