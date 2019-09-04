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
struct atmel_i2s_dev {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_I2SC_IMR ; 
 unsigned int ATMEL_I2SC_INT_RXOR ; 
 unsigned int ATMEL_I2SC_INT_TXUR ; 
 unsigned int ATMEL_I2SC_MAX_TDM_CHANNELS ; 
 int /*<<< orphan*/  ATMEL_I2SC_SCR ; 
 int /*<<< orphan*/  ATMEL_I2SC_SR ; 
 unsigned int ATMEL_I2SC_SR_RXOR ; 
 unsigned int ATMEL_I2SC_SR_RXORCH (unsigned int) ; 
 unsigned int ATMEL_I2SC_SR_TXUR ; 
 unsigned int ATMEL_I2SC_SR_TXURCH (unsigned int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static irqreturn_t atmel_i2s_interrupt(int irq, void *dev_id)
{
	struct atmel_i2s_dev *dev = dev_id;
	unsigned int sr, imr, pending, ch, mask;
	irqreturn_t ret = IRQ_NONE;

	regmap_read(dev->regmap, ATMEL_I2SC_SR, &sr);
	regmap_read(dev->regmap, ATMEL_I2SC_IMR, &imr);
	pending = sr & imr;

	if (!pending)
		return IRQ_NONE;

	if (pending & ATMEL_I2SC_INT_RXOR) {
		mask = ATMEL_I2SC_SR_RXOR;

		for (ch = 0; ch < ATMEL_I2SC_MAX_TDM_CHANNELS; ++ch) {
			if (sr & ATMEL_I2SC_SR_RXORCH(ch)) {
				mask |= ATMEL_I2SC_SR_RXORCH(ch);
				dev_err(dev->dev,
					"RX overrun on channel %d\n", ch);
			}
		}
		regmap_write(dev->regmap, ATMEL_I2SC_SCR, mask);
		ret = IRQ_HANDLED;
	}

	if (pending & ATMEL_I2SC_INT_TXUR) {
		mask = ATMEL_I2SC_SR_TXUR;

		for (ch = 0; ch < ATMEL_I2SC_MAX_TDM_CHANNELS; ++ch) {
			if (sr & ATMEL_I2SC_SR_TXURCH(ch)) {
				mask |= ATMEL_I2SC_SR_TXURCH(ch);
				dev_err(dev->dev,
					"TX underrun on channel %d\n", ch);
			}
		}
		regmap_write(dev->regmap, ATMEL_I2SC_SCR, mask);
		ret = IRQ_HANDLED;
	}

	return ret;
}