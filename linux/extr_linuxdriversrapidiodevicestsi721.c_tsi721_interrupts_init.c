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
typedef  int u32 ;
struct tsi721_device {int flags; scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDB_QUEUE ; 
 scalar_t__ TSI721_DEV_CHAN_INTE ; 
 scalar_t__ TSI721_DEV_INTE ; 
 int TSI721_DEV_INT_BDMA_CH ; 
 int TSI721_DEV_INT_SMSG_CH ; 
 int TSI721_DEV_INT_SR2PC_CH ; 
 int TSI721_DEV_INT_SRIO ; 
 int TSI721_INT_SR2PC_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ TSI721_RIO_EM_DEV_INT_EN ; 
 int TSI721_RIO_EM_DEV_INT_EN_INT ; 
 scalar_t__ TSI721_SR_CHINT (int /*<<< orphan*/ ) ; 
 scalar_t__ TSI721_SR_CHINTE (int /*<<< orphan*/ ) ; 
 int TSI721_SR_CHINT_ALL ; 
 int TSI721_SR_CHINT_IDBQRCV ; 
 int TSI721_USING_MSIX ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void tsi721_interrupts_init(struct tsi721_device *priv)
{
	u32 intr;

	/* Enable IDB interrupts */
	iowrite32(TSI721_SR_CHINT_ALL,
		priv->regs + TSI721_SR_CHINT(IDB_QUEUE));
	iowrite32(TSI721_SR_CHINT_IDBQRCV,
		priv->regs + TSI721_SR_CHINTE(IDB_QUEUE));

	/* Enable SRIO MAC interrupts */
	iowrite32(TSI721_RIO_EM_DEV_INT_EN_INT,
		priv->regs + TSI721_RIO_EM_DEV_INT_EN);

	/* Enable interrupts from channels in use */
#ifdef CONFIG_RAPIDIO_DMA_ENGINE
	intr = TSI721_INT_SR2PC_CHAN(IDB_QUEUE) |
		(TSI721_INT_BDMA_CHAN_M &
		 ~TSI721_INT_BDMA_CHAN(TSI721_DMACH_MAINT));
#else
	intr = TSI721_INT_SR2PC_CHAN(IDB_QUEUE);
#endif
	iowrite32(intr,	priv->regs + TSI721_DEV_CHAN_INTE);

	if (priv->flags & TSI721_USING_MSIX)
		intr = TSI721_DEV_INT_SRIO;
	else
		intr = TSI721_DEV_INT_SR2PC_CH | TSI721_DEV_INT_SRIO |
			TSI721_DEV_INT_SMSG_CH | TSI721_DEV_INT_BDMA_CH;

	iowrite32(intr, priv->regs + TSI721_DEV_INTE);
	ioread32(priv->regs + TSI721_DEV_INTE);
}