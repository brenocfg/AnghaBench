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
struct qeth_cmd_buffer {int /*<<< orphan*/  data; } ;
struct qeth_channel {scalar_t__ state; int /*<<< orphan*/  irq_pending; int /*<<< orphan*/  ccw; int /*<<< orphan*/  ccwdev; } ;
struct qeth_card {int read_or_write_problem; int /*<<< orphan*/  wait_q; TYPE_1__* gdev; struct qeth_channel read; } ;
typedef  int /*<<< orphan*/  addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_CMD_READ ; 
 scalar_t__ CH_STATE_UP ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  QETH_BUFSIZE ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ccw_device_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct qeth_cmd_buffer* qeth_get_buffer (struct qeth_channel*) ; 
 int /*<<< orphan*/  qeth_release_buffer (struct qeth_channel*,struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  qeth_schedule_recovery (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_setup_ccw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __qeth_issue_next_read(struct qeth_card *card)
{
	struct qeth_channel *channel = &card->read;
	struct qeth_cmd_buffer *iob;
	int rc;

	QETH_CARD_TEXT(card, 5, "issnxrd");
	if (channel->state != CH_STATE_UP)
		return -EIO;
	iob = qeth_get_buffer(channel);
	if (!iob) {
		dev_warn(&card->gdev->dev, "The qeth device driver "
			"failed to recover an error on the device\n");
		QETH_DBF_MESSAGE(2, "%s issue_next_read failed: no iob "
			"available\n", dev_name(&card->gdev->dev));
		return -ENOMEM;
	}
	qeth_setup_ccw(channel->ccw, CCW_CMD_READ, QETH_BUFSIZE, iob->data);
	QETH_CARD_TEXT(card, 6, "noirqpnd");
	rc = ccw_device_start(channel->ccwdev, channel->ccw,
			      (addr_t) iob, 0, 0);
	if (rc) {
		QETH_DBF_MESSAGE(2, "%s error in starting next read ccw! "
			"rc=%i\n", dev_name(&card->gdev->dev), rc);
		atomic_set(&channel->irq_pending, 0);
		qeth_release_buffer(channel, iob);
		card->read_or_write_problem = 1;
		qeth_schedule_recovery(card);
		wake_up(&card->wait_q);
	}
	return rc;
}