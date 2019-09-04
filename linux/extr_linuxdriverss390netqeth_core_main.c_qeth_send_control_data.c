#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct qeth_reply {int (* callback ) (struct qeth_card*,struct qeth_reply*,unsigned long) ;int rc; int /*<<< orphan*/  received; TYPE_3__* card; int /*<<< orphan*/  list; int /*<<< orphan*/  wait_q; scalar_t__ seqno; void* param; } ;
struct TYPE_7__ {scalar_t__ command; scalar_t__ prot_version; scalar_t__ seqno; } ;
struct qeth_ipa_cmd {TYPE_2__ hdr; } ;
struct qeth_cmd_buffer {int /*<<< orphan*/  data; struct qeth_channel* channel; } ;
struct qeth_channel {int /*<<< orphan*/  irq_pending; TYPE_4__* ccwdev; int /*<<< orphan*/  ccw; } ;
struct TYPE_6__ {int /*<<< orphan*/  ipa; } ;
struct qeth_card {int /*<<< orphan*/  wait_q; int /*<<< orphan*/  lock; int /*<<< orphan*/  cmd_waiter_list; TYPE_1__ seqno; scalar_t__ read_or_write_problem; } ;
typedef  int /*<<< orphan*/  addr_t ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int ETIME ; 
 scalar_t__ IPA_CMD_SETIP ; 
 scalar_t__ IS_IPA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ QETH_IDX_COMMAND_SEQNO ; 
 unsigned long QETH_IPA_TIMEOUT ; 
 scalar_t__ QETH_PROT_IPV4 ; 
 unsigned long QETH_TIMEOUT ; 
 struct qeth_ipa_cmd* __ipa_cmd (struct qeth_cmd_buffer*) ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ccw_device_start_timeout (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_ccwdev_lock (TYPE_4__*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 struct qeth_reply* qeth_alloc_reply (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_prepare_control_data (struct qeth_card*,int,struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  qeth_put_reply (struct qeth_reply*) ; 
 int /*<<< orphan*/  qeth_release_buffer (struct qeth_channel*,struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int qeth_send_control_data(struct qeth_card *card, int len,
		struct qeth_cmd_buffer *iob,
		int (*reply_cb)(struct qeth_card *cb_card,
				struct qeth_reply *cb_reply,
				unsigned long cb_cmd),
		void *reply_param)
{
	struct qeth_channel *channel = iob->channel;
	int rc;
	unsigned long flags;
	struct qeth_reply *reply = NULL;
	unsigned long timeout, event_timeout;
	struct qeth_ipa_cmd *cmd = NULL;

	QETH_CARD_TEXT(card, 2, "sendctl");

	if (card->read_or_write_problem) {
		qeth_release_buffer(channel, iob);
		return -EIO;
	}
	reply = qeth_alloc_reply(card);
	if (!reply) {
		qeth_release_buffer(channel, iob);
		return -ENOMEM;
	}
	reply->callback = reply_cb;
	reply->param = reply_param;

	init_waitqueue_head(&reply->wait_q);

	while (atomic_cmpxchg(&channel->irq_pending, 0, 1)) ;

	if (IS_IPA(iob->data)) {
		cmd = __ipa_cmd(iob);
		cmd->hdr.seqno = card->seqno.ipa++;
		reply->seqno = cmd->hdr.seqno;
		event_timeout = QETH_IPA_TIMEOUT;
	} else {
		reply->seqno = QETH_IDX_COMMAND_SEQNO;
		event_timeout = QETH_TIMEOUT;
	}
	qeth_prepare_control_data(card, len, iob);

	spin_lock_irqsave(&card->lock, flags);
	list_add_tail(&reply->list, &card->cmd_waiter_list);
	spin_unlock_irqrestore(&card->lock, flags);

	timeout = jiffies + event_timeout;

	QETH_CARD_TEXT(card, 6, "noirqpnd");
	spin_lock_irqsave(get_ccwdev_lock(channel->ccwdev), flags);
	rc = ccw_device_start_timeout(channel->ccwdev, channel->ccw,
				      (addr_t) iob, 0, 0, event_timeout);
	spin_unlock_irqrestore(get_ccwdev_lock(channel->ccwdev), flags);
	if (rc) {
		QETH_DBF_MESSAGE(2, "%s qeth_send_control_data: "
			"ccw_device_start rc = %i\n",
			dev_name(&channel->ccwdev->dev), rc);
		QETH_CARD_TEXT_(card, 2, " err%d", rc);
		spin_lock_irqsave(&card->lock, flags);
		list_del_init(&reply->list);
		qeth_put_reply(reply);
		spin_unlock_irqrestore(&card->lock, flags);
		qeth_release_buffer(channel, iob);
		atomic_set(&channel->irq_pending, 0);
		wake_up(&card->wait_q);
		return rc;
	}

	/* we have only one long running ipassist, since we can ensure
	   process context of this command we can sleep */
	if (cmd && cmd->hdr.command == IPA_CMD_SETIP &&
	    cmd->hdr.prot_version == QETH_PROT_IPV4) {
		if (!wait_event_timeout(reply->wait_q,
		    atomic_read(&reply->received), event_timeout))
			goto time_err;
	} else {
		while (!atomic_read(&reply->received)) {
			if (time_after(jiffies, timeout))
				goto time_err;
			cpu_relax();
		}
	}

	rc = reply->rc;
	qeth_put_reply(reply);
	return rc;

time_err:
	reply->rc = -ETIME;
	spin_lock_irqsave(&reply->card->lock, flags);
	list_del_init(&reply->list);
	spin_unlock_irqrestore(&reply->card->lock, flags);
	atomic_inc(&reply->received);
	rc = reply->rc;
	qeth_put_reply(reply);
	return rc;
}