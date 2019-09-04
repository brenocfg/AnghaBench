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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct fsl_spdif_priv {struct platform_device* pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int INT_BIT_ERR ; 
 int INT_CNEW ; 
 int INT_DPLL_LOCKED ; 
 int INT_LOSS_LOCK ; 
 int INT_QRX_FUL ; 
 int INT_QRX_OV ; 
 int INT_RXFIFO_FUL ; 
 int INT_RXFIFO_RESYNC ; 
 int INT_RXFIFO_UNOV ; 
 int INT_SYM_ERR ; 
 int INT_TXFIFO_RESYNC ; 
 int INT_TXFIFO_UNOV ; 
 int INT_TX_EM ; 
 int INT_UQ_ERR ; 
 int INT_UQ_SYNC ; 
 int INT_URX_FUL ; 
 int INT_URX_OV ; 
 int INT_VAL_NOGOOD ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int spdif_intr_status_clear (struct fsl_spdif_priv*) ; 
 int /*<<< orphan*/  spdif_irq_dpll_lock (struct fsl_spdif_priv*) ; 
 int /*<<< orphan*/  spdif_irq_sym_error (struct fsl_spdif_priv*) ; 
 int /*<<< orphan*/  spdif_irq_uq_err (struct fsl_spdif_priv*) ; 
 int /*<<< orphan*/  spdif_irq_uq_sync (struct fsl_spdif_priv*) ; 
 int /*<<< orphan*/  spdif_irq_uqrx_full (struct fsl_spdif_priv*,char) ; 

__attribute__((used)) static irqreturn_t spdif_isr(int irq, void *devid)
{
	struct fsl_spdif_priv *spdif_priv = (struct fsl_spdif_priv *)devid;
	struct platform_device *pdev = spdif_priv->pdev;
	u32 sis;

	sis = spdif_intr_status_clear(spdif_priv);

	if (sis & INT_DPLL_LOCKED)
		spdif_irq_dpll_lock(spdif_priv);

	if (sis & INT_TXFIFO_UNOV)
		dev_dbg(&pdev->dev, "isr: Tx FIFO under/overrun\n");

	if (sis & INT_TXFIFO_RESYNC)
		dev_dbg(&pdev->dev, "isr: Tx FIFO resync\n");

	if (sis & INT_CNEW)
		dev_dbg(&pdev->dev, "isr: cstatus new\n");

	if (sis & INT_VAL_NOGOOD)
		dev_dbg(&pdev->dev, "isr: validity flag no good\n");

	if (sis & INT_SYM_ERR)
		spdif_irq_sym_error(spdif_priv);

	if (sis & INT_BIT_ERR)
		dev_dbg(&pdev->dev, "isr: receiver found parity bit error\n");

	if (sis & INT_URX_FUL)
		spdif_irq_uqrx_full(spdif_priv, 'U');

	if (sis & INT_URX_OV)
		dev_dbg(&pdev->dev, "isr: U Channel receive register overrun\n");

	if (sis & INT_QRX_FUL)
		spdif_irq_uqrx_full(spdif_priv, 'Q');

	if (sis & INT_QRX_OV)
		dev_dbg(&pdev->dev, "isr: Q Channel receive register overrun\n");

	if (sis & INT_UQ_SYNC)
		spdif_irq_uq_sync(spdif_priv);

	if (sis & INT_UQ_ERR)
		spdif_irq_uq_err(spdif_priv);

	if (sis & INT_RXFIFO_UNOV)
		dev_dbg(&pdev->dev, "isr: Rx FIFO under/overrun\n");

	if (sis & INT_RXFIFO_RESYNC)
		dev_dbg(&pdev->dev, "isr: Rx FIFO resync\n");

	if (sis & INT_LOSS_LOCK)
		spdif_irq_dpll_lock(spdif_priv);

	/* FIXME: Write Tx FIFO to clear TxEm */
	if (sis & INT_TX_EM)
		dev_dbg(&pdev->dev, "isr: Tx FIFO empty\n");

	/* FIXME: Read Rx FIFO to clear RxFIFOFul */
	if (sis & INT_RXFIFO_FUL)
		dev_dbg(&pdev->dev, "isr: Rx FIFO full\n");

	return IRQ_HANDLED;
}