#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct rio_mport {TYPE_2__* inb_msg; } ;
struct tsi721_device {int flags; TYPE_3__* imsg_ring; scalar_t__ regs; TYPE_1__* pdev; struct rio_mport mport; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* mcback ) (struct rio_mport*,int /*<<< orphan*/ ,size_t,int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ TSI721_DEV_CHAN_INTE ; 
 scalar_t__ TSI721_IBDMAC_INT (int) ; 
 size_t TSI721_IBDMAC_INT_DQ_RCV ; 
 size_t TSI721_IBDMAC_INT_FQ_LOW ; 
 size_t TSI721_IBDMAC_INT_PC_ERROR ; 
 size_t TSI721_IBDMAC_INT_SRTO ; 
 size_t TSI721_INT_IMSG_CHAN (int) ; 
 int TSI721_USING_MSIX ; 
 size_t ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (size_t,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rio_mport*,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  tsi_info (int /*<<< orphan*/ *,char*,size_t) ; 

__attribute__((used)) static void tsi721_imsg_handler(struct tsi721_device *priv, int ch)
{
	u32 mbox = ch - 4;
	u32 imsg_int;
	struct rio_mport *mport = &priv->mport;

	spin_lock(&priv->imsg_ring[mbox].lock);

	imsg_int = ioread32(priv->regs + TSI721_IBDMAC_INT(ch));

	if (imsg_int & TSI721_IBDMAC_INT_SRTO)
		tsi_info(&priv->pdev->dev, "IB MBOX%d SRIO timeout", mbox);

	if (imsg_int & TSI721_IBDMAC_INT_PC_ERROR)
		tsi_info(&priv->pdev->dev, "IB MBOX%d PCIe error", mbox);

	if (imsg_int & TSI721_IBDMAC_INT_FQ_LOW)
		tsi_info(&priv->pdev->dev, "IB MBOX%d IB free queue low", mbox);

	/* Clear IB channel interrupts */
	iowrite32(imsg_int, priv->regs + TSI721_IBDMAC_INT(ch));

	/* If an IB Msg is received notify the upper layer */
	if (imsg_int & TSI721_IBDMAC_INT_DQ_RCV &&
		mport->inb_msg[mbox].mcback)
		mport->inb_msg[mbox].mcback(mport,
				priv->imsg_ring[mbox].dev_id, mbox, -1);

	if (!(priv->flags & TSI721_USING_MSIX)) {
		u32 ch_inte;

		/* Re-enable channel interrupts */
		ch_inte = ioread32(priv->regs + TSI721_DEV_CHAN_INTE);
		ch_inte |= TSI721_INT_IMSG_CHAN(ch);
		iowrite32(ch_inte, priv->regs + TSI721_DEV_CHAN_INTE);
	}

	spin_unlock(&priv->imsg_ring[mbox].lock);
}