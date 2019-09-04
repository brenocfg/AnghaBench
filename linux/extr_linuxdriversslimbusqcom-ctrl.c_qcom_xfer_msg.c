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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct slim_msg_txn {scalar_t__ dt; int ec; int /*<<< orphan*/  mt; int /*<<< orphan*/  mc; int /*<<< orphan*/  rl; TYPE_1__* msg; int /*<<< orphan*/  tid; int /*<<< orphan*/  la; } ;
struct slim_controller {int /*<<< orphan*/  dev; } ;
struct qcom_slim_ctrl {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_bytes; int /*<<< orphan*/  wbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  MGR_TX_MSG ; 
 int QCOM_BUF_ALLOC_RETRIES ; 
 int /*<<< orphan*/  SLIM_MSG_ASM_FIRST_WORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ SLIM_MSG_DEST_LOGICALADDR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qcom_slim_ctrl* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  qcom_slim_queue_tx (struct qcom_slim_ctrl*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* slim_alloc_txbuf (struct qcom_slim_ctrl*,struct slim_msg_txn*,int /*<<< orphan*/ *) ; 
 scalar_t__ slim_ec_txn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ slim_tid_txn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_xfer_msg(struct slim_controller *sctrl,
			 struct slim_msg_txn *txn)
{
	struct qcom_slim_ctrl *ctrl = dev_get_drvdata(sctrl->dev);
	DECLARE_COMPLETION_ONSTACK(done);
	void *pbuf = slim_alloc_txbuf(ctrl, txn, &done);
	unsigned long ms = txn->rl + HZ;
	u8 *puc;
	int ret = 0, timeout, retries = QCOM_BUF_ALLOC_RETRIES;
	u8 la = txn->la;
	u32 *head;
	/* HW expects length field to be excluded */
	txn->rl--;

	/* spin till buffer is made available */
	if (!pbuf) {
		while (retries--) {
			usleep_range(10000, 15000);
			pbuf = slim_alloc_txbuf(ctrl, txn, &done);
			if (pbuf)
				break;
		}
	}

	if (retries < 0 && !pbuf)
		return -ENOMEM;

	puc = (u8 *)pbuf;
	head = (u32 *)pbuf;

	if (txn->dt == SLIM_MSG_DEST_LOGICALADDR) {
		*head = SLIM_MSG_ASM_FIRST_WORD(txn->rl, txn->mt,
						txn->mc, 0, la);
		puc += 3;
	} else {
		*head = SLIM_MSG_ASM_FIRST_WORD(txn->rl, txn->mt,
						txn->mc, 1, la);
		puc += 2;
	}

	if (slim_tid_txn(txn->mt, txn->mc))
		*(puc++) = txn->tid;

	if (slim_ec_txn(txn->mt, txn->mc)) {
		*(puc++) = (txn->ec & 0xFF);
		*(puc++) = (txn->ec >> 8) & 0xFF;
	}

	if (txn->msg && txn->msg->wbuf)
		memcpy(puc, txn->msg->wbuf, txn->msg->num_bytes);

	qcom_slim_queue_tx(ctrl, head, txn->rl, MGR_TX_MSG);
	timeout = wait_for_completion_timeout(&done, msecs_to_jiffies(ms));

	if (!timeout) {
		dev_err(ctrl->dev, "TX timed out:MC:0x%x,mt:0x%x", txn->mc,
					txn->mt);
		ret = -ETIMEDOUT;
	}

	return ret;

}