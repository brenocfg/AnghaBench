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
struct ep93xx_i2s_info {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  EP93XX_I2S_GLSTS ; 
 int EP93XX_I2S_GLSTS_TX0_FIFO_FULL ; 
 int /*<<< orphan*/  EP93XX_I2S_I2STX0LFT ; 
 int /*<<< orphan*/  EP93XX_I2S_I2STX0RT ; 
 int /*<<< orphan*/  EP93XX_I2S_TX0EN ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int ep93xx_i2s_read_reg (struct ep93xx_i2s_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep93xx_i2s_write_reg (struct ep93xx_i2s_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t ep93xx_i2s_interrupt(int irq, void *dev_id)
{
	struct ep93xx_i2s_info *info = dev_id;

	/* Disable FIFO */
	ep93xx_i2s_write_reg(info, EP93XX_I2S_TX0EN, 0);
	/*
	 * Fill TX FIFO with zeroes, this way we can defer next IRQs as much as
	 * possible and get more time for DMA to catch up. Actually there are
	 * only 8 samples in this FIFO, so even on 8kHz maximum deferral here is
	 * 1ms.
	 */
	while (!(ep93xx_i2s_read_reg(info, EP93XX_I2S_GLSTS) &
		 EP93XX_I2S_GLSTS_TX0_FIFO_FULL)) {
		ep93xx_i2s_write_reg(info, EP93XX_I2S_I2STX0LFT, 0);
		ep93xx_i2s_write_reg(info, EP93XX_I2S_I2STX0RT, 0);
	}
	/* Re-enable FIFO */
	ep93xx_i2s_write_reg(info, EP93XX_I2S_TX0EN, 1);

	return IRQ_HANDLED;
}