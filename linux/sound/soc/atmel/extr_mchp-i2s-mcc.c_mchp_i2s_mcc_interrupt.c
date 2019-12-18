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
struct mchp_i2s_mcc_dev {int tx_rdy; int rx_rdy; int /*<<< orphan*/  regmap; int /*<<< orphan*/  wq_rxrdy; int /*<<< orphan*/  channels; int /*<<< orphan*/  wq_txrdy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  MCHP_I2SMCC_IDRA ; 
 int /*<<< orphan*/  MCHP_I2SMCC_IMRA ; 
 int /*<<< orphan*/  MCHP_I2SMCC_IMRB ; 
 int MCHP_I2SMCC_INT_RXRDY_MASK (int /*<<< orphan*/ ) ; 
 int MCHP_I2SMCC_INT_TXRDY_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCHP_I2SMCC_ISRA ; 
 int /*<<< orphan*/  MCHP_I2SMCC_ISRB ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mchp_i2s_mcc_interrupt(int irq, void *dev_id)
{
	struct mchp_i2s_mcc_dev *dev = dev_id;
	u32 sra, imra, srb, imrb, pendinga, pendingb, idra = 0;
	irqreturn_t ret = IRQ_NONE;

	regmap_read(dev->regmap, MCHP_I2SMCC_IMRA, &imra);
	regmap_read(dev->regmap, MCHP_I2SMCC_ISRA, &sra);
	pendinga = imra & sra;

	regmap_read(dev->regmap, MCHP_I2SMCC_IMRB, &imrb);
	regmap_read(dev->regmap, MCHP_I2SMCC_ISRB, &srb);
	pendingb = imrb & srb;

	if (!pendinga && !pendingb)
		return IRQ_NONE;

	/*
	 * Tx/Rx ready interrupts are enabled when stopping only, to assure
	 * availability and to disable clocks if necessary
	 */
	idra |= pendinga & (MCHP_I2SMCC_INT_TXRDY_MASK(dev->channels) |
			    MCHP_I2SMCC_INT_RXRDY_MASK(dev->channels));
	if (idra)
		ret = IRQ_HANDLED;

	if ((imra & MCHP_I2SMCC_INT_TXRDY_MASK(dev->channels)) &&
	    (imra & MCHP_I2SMCC_INT_TXRDY_MASK(dev->channels)) ==
	    (idra & MCHP_I2SMCC_INT_TXRDY_MASK(dev->channels))) {
		dev->tx_rdy = 1;
		wake_up_interruptible(&dev->wq_txrdy);
	}
	if ((imra & MCHP_I2SMCC_INT_RXRDY_MASK(dev->channels)) &&
	    (imra & MCHP_I2SMCC_INT_RXRDY_MASK(dev->channels)) ==
	    (idra & MCHP_I2SMCC_INT_RXRDY_MASK(dev->channels))) {
		dev->rx_rdy = 1;
		wake_up_interruptible(&dev->wq_rxrdy);
	}
	regmap_write(dev->regmap, MCHP_I2SMCC_IDRA, idra);

	return ret;
}