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
struct qcom_glink {int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  mbox_chan; TYPE_1__* tx_pipe; } ;
struct TYPE_2__ {unsigned int length; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  mbox_client_txdone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int qcom_glink_tx_avail (struct qcom_glink*) ; 
 int /*<<< orphan*/  qcom_glink_tx_write (struct qcom_glink*,void const*,size_t,void const*,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int qcom_glink_tx(struct qcom_glink *glink,
			 const void *hdr, size_t hlen,
			 const void *data, size_t dlen, bool wait)
{
	unsigned int tlen = hlen + dlen;
	unsigned long flags;
	int ret = 0;

	/* Reject packets that are too big */
	if (tlen >= glink->tx_pipe->length)
		return -EINVAL;

	spin_lock_irqsave(&glink->tx_lock, flags);

	while (qcom_glink_tx_avail(glink) < tlen) {
		if (!wait) {
			ret = -EAGAIN;
			goto out;
		}

		/* Wait without holding the tx_lock */
		spin_unlock_irqrestore(&glink->tx_lock, flags);

		usleep_range(10000, 15000);

		spin_lock_irqsave(&glink->tx_lock, flags);
	}

	qcom_glink_tx_write(glink, hdr, hlen, data, dlen);

	mbox_send_message(glink->mbox_chan, NULL);
	mbox_client_txdone(glink->mbox_chan, 0);

out:
	spin_unlock_irqrestore(&glink->tx_lock, flags);

	return ret;
}