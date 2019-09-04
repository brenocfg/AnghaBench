#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct tsi721_imsg_desc {int dummy; } ;
struct tsi721_device {TYPE_2__* imsg_ring; TYPE_1__* pdev; scalar_t__* imsg_init; } ;
struct rio_mport {struct tsi721_device* priv; } ;
struct TYPE_4__ {size_t size; int /*<<< orphan*/ * imd_base; int /*<<< orphan*/  imd_phys; int /*<<< orphan*/ * imfq_base; int /*<<< orphan*/  imfq_phys; int /*<<< orphan*/ * buf_base; int /*<<< orphan*/  buf_phys; int /*<<< orphan*/ ** imq_base; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int TSI721_MSG_BUFFER_SIZE ; 
 int /*<<< orphan*/  TSI721_OBDMAC_INT_MASK ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi721_imsg_interrupt_disable (struct tsi721_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tsi721_close_inb_mbox(struct rio_mport *mport, int mbox)
{
	struct tsi721_device *priv = mport->priv;
	u32 rx_slot;
	int ch = mbox + 4;

	if (!priv->imsg_init[mbox]) /* mbox isn't initialized yet */
		return;
	priv->imsg_init[mbox] = 0;

	/* Disable Inbound Messaging Engine */

	/* Disable Interrupts */
	tsi721_imsg_interrupt_disable(priv, ch, TSI721_OBDMAC_INT_MASK);

#ifdef CONFIG_PCI_MSI
	if (priv->flags & TSI721_USING_MSIX) {
		free_irq(priv->msix[TSI721_VECT_IMB0_RCV + mbox].vector,
				(void *)priv);
		free_irq(priv->msix[TSI721_VECT_IMB0_INT + mbox].vector,
				(void *)priv);
	}
#endif /* CONFIG_PCI_MSI */

	/* Clear Inbound Buffer Queue */
	for (rx_slot = 0; rx_slot < priv->imsg_ring[mbox].size; rx_slot++)
		priv->imsg_ring[mbox].imq_base[rx_slot] = NULL;

	/* Free memory allocated for message buffers */
	dma_free_coherent(&priv->pdev->dev,
		priv->imsg_ring[mbox].size * TSI721_MSG_BUFFER_SIZE,
		priv->imsg_ring[mbox].buf_base,
		priv->imsg_ring[mbox].buf_phys);

	priv->imsg_ring[mbox].buf_base = NULL;

	/* Free memory allocated for free pointr list */
	dma_free_coherent(&priv->pdev->dev,
		priv->imsg_ring[mbox].size * 8,
		priv->imsg_ring[mbox].imfq_base,
		priv->imsg_ring[mbox].imfq_phys);

	priv->imsg_ring[mbox].imfq_base = NULL;

	/* Free memory allocated for RX descriptors */
	dma_free_coherent(&priv->pdev->dev,
		priv->imsg_ring[mbox].size * sizeof(struct tsi721_imsg_desc),
		priv->imsg_ring[mbox].imd_base,
		priv->imsg_ring[mbox].imd_phys);

	priv->imsg_ring[mbox].imd_base = NULL;
}