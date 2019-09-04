#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct qeth_cmd_buffer {void (* callback ) (struct qeth_channel*,struct qeth_cmd_buffer*) ;int /*<<< orphan*/  data; } ;
struct qeth_channel {scalar_t__ state; TYPE_5__* ccwdev; int /*<<< orphan*/  irq_pending; int /*<<< orphan*/  ccw; } ;
struct TYPE_11__ {int func_level; int cula; int unit_addr2; } ;
struct TYPE_10__ {int issuer_rm_w; } ;
struct TYPE_8__ {int trans_hdr; } ;
struct qeth_card {int /*<<< orphan*/  wait_q; TYPE_4__ info; TYPE_3__ token; TYPE_2__* dev; TYPE_1__ seqno; struct qeth_channel write; } ;
struct ccw_dev_id {int devno; } ;
typedef  int /*<<< orphan*/  addr_t ;
typedef  int __u8 ;
typedef  int __u16 ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {scalar_t__ dev_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DDEV (struct qeth_card*) ; 
 struct qeth_card* CARD_FROM_CDEV (TYPE_5__*) ; 
 int /*<<< orphan*/  CCW_CMD_WRITE ; 
 scalar_t__ CH_STATE_ACTIVATING ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int ETIME ; 
 int* IDX_ACTIVATE_READ ; 
 int IDX_ACTIVATE_SIZE ; 
 int* IDX_ACTIVATE_WRITE ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  QETH_IDX_ACT_FUNC_LEVEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_IDX_ACT_ISSUER_RM_TOKEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_IDX_ACT_PNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_IDX_ACT_QDIO_DEV_CUA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_IDX_ACT_QDIO_DEV_REALADDR (int /*<<< orphan*/ ) ; 
 int QETH_MPC_TOKEN_LENGTH ; 
 int QETH_SEQ_NO_LENGTH ; 
 int /*<<< orphan*/  QETH_TIMEOUT ; 
 int /*<<< orphan*/  QETH_TRANSPORT_HEADER_SEQ_NO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETUP ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_get_id (int /*<<< orphan*/ ,struct ccw_dev_id*) ; 
 int ccw_device_start_timeout (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (TYPE_5__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 struct qeth_cmd_buffer* qeth_get_buffer (struct qeth_channel*) ; 
 int qeth_idx_activate_get_answer (struct qeth_channel*,void (*) (struct qeth_channel*,struct qeth_cmd_buffer*)) ; 
 int /*<<< orphan*/  qeth_release_buffer (struct qeth_channel*,struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  qeth_setup_ccw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qeth_idx_activate_channel(struct qeth_channel *channel,
		void (*idx_reply_cb)(struct qeth_channel *,
			struct qeth_cmd_buffer *))
{
	struct qeth_card *card;
	struct qeth_cmd_buffer *iob;
	unsigned long flags;
	__u16 temp;
	__u8 tmp;
	int rc;
	struct ccw_dev_id temp_devid;

	card = CARD_FROM_CDEV(channel->ccwdev);

	QETH_DBF_TEXT(SETUP, 2, "idxactch");

	iob = qeth_get_buffer(channel);
	if (!iob)
		return -ENOMEM;
	iob->callback = idx_reply_cb;
	qeth_setup_ccw(channel->ccw, CCW_CMD_WRITE, IDX_ACTIVATE_SIZE,
		       iob->data);
	if (channel == &card->write) {
		memcpy(iob->data, IDX_ACTIVATE_WRITE, IDX_ACTIVATE_SIZE);
		memcpy(QETH_TRANSPORT_HEADER_SEQ_NO(iob->data),
		       &card->seqno.trans_hdr, QETH_SEQ_NO_LENGTH);
		card->seqno.trans_hdr++;
	} else {
		memcpy(iob->data, IDX_ACTIVATE_READ, IDX_ACTIVATE_SIZE);
		memcpy(QETH_TRANSPORT_HEADER_SEQ_NO(iob->data),
		       &card->seqno.trans_hdr, QETH_SEQ_NO_LENGTH);
	}
	tmp = ((u8)card->dev->dev_port) | 0x80;
	memcpy(QETH_IDX_ACT_PNO(iob->data), &tmp, 1);
	memcpy(QETH_IDX_ACT_ISSUER_RM_TOKEN(iob->data),
	       &card->token.issuer_rm_w, QETH_MPC_TOKEN_LENGTH);
	memcpy(QETH_IDX_ACT_FUNC_LEVEL(iob->data),
	       &card->info.func_level, sizeof(__u16));
	ccw_device_get_id(CARD_DDEV(card), &temp_devid);
	memcpy(QETH_IDX_ACT_QDIO_DEV_CUA(iob->data), &temp_devid.devno, 2);
	temp = (card->info.cula << 8) + card->info.unit_addr2;
	memcpy(QETH_IDX_ACT_QDIO_DEV_REALADDR(iob->data), &temp, 2);

	wait_event(card->wait_q,
		   atomic_cmpxchg(&channel->irq_pending, 0, 1) == 0);
	QETH_DBF_TEXT(SETUP, 6, "noirqpnd");
	spin_lock_irqsave(get_ccwdev_lock(channel->ccwdev), flags);
	rc = ccw_device_start_timeout(channel->ccwdev, channel->ccw,
				      (addr_t) iob, 0, 0, QETH_TIMEOUT);
	spin_unlock_irqrestore(get_ccwdev_lock(channel->ccwdev), flags);

	if (rc) {
		QETH_DBF_MESSAGE(2, "Error1 in activating channel. rc=%d\n",
			rc);
		QETH_DBF_TEXT_(SETUP, 2, "1err%d", rc);
		atomic_set(&channel->irq_pending, 0);
		qeth_release_buffer(channel, iob);
		wake_up(&card->wait_q);
		return rc;
	}
	rc = wait_event_interruptible_timeout(card->wait_q,
			channel->state == CH_STATE_ACTIVATING, QETH_TIMEOUT);
	if (rc == -ERESTARTSYS)
		return rc;
	if (channel->state != CH_STATE_ACTIVATING) {
		dev_warn(&channel->ccwdev->dev, "The qeth device driver"
			" failed to recover an error on the device\n");
		QETH_DBF_MESSAGE(2, "%s IDX activate timed out\n",
			dev_name(&channel->ccwdev->dev));
		QETH_DBF_TEXT_(SETUP, 2, "2err%d", -ETIME);
		return -ETIME;
	}
	return qeth_idx_activate_get_answer(channel, idx_reply_cb);
}