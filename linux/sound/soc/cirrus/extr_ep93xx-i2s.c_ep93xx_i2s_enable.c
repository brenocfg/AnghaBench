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
struct ep93xx_i2s_info {int /*<<< orphan*/  lrclk; int /*<<< orphan*/  sclk; int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SND_EP93XX_SOC_I2S_WATCHDOG ; 
 unsigned int EP93XX_I2S_GLCTRL ; 
 unsigned int EP93XX_I2S_RX0EN ; 
 unsigned int EP93XX_I2S_TX0EN ; 
 unsigned int EP93XX_I2S_TXCTRL ; 
 int EP93XX_I2S_TXCTRL_TXEMPTY_LVL ; 
 int EP93XX_I2S_TXCTRL_TXUFIE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int ep93xx_i2s_read_reg (struct ep93xx_i2s_info*,unsigned int) ; 
 int /*<<< orphan*/  ep93xx_i2s_write_reg (struct ep93xx_i2s_info*,unsigned int,int) ; 

__attribute__((used)) static void ep93xx_i2s_enable(struct ep93xx_i2s_info *info, int stream)
{
	unsigned base_reg;

	if ((ep93xx_i2s_read_reg(info, EP93XX_I2S_TX0EN) & 0x1) == 0 &&
	    (ep93xx_i2s_read_reg(info, EP93XX_I2S_RX0EN) & 0x1) == 0) {
		/* Enable clocks */
		clk_enable(info->mclk);
		clk_enable(info->sclk);
		clk_enable(info->lrclk);

		/* Enable i2s */
		ep93xx_i2s_write_reg(info, EP93XX_I2S_GLCTRL, 1);
	}

	/* Enable fifo */
	if (stream == SNDRV_PCM_STREAM_PLAYBACK)
		base_reg = EP93XX_I2S_TX0EN;
	else
		base_reg = EP93XX_I2S_RX0EN;
	ep93xx_i2s_write_reg(info, base_reg, 1);

	/* Enable TX IRQs (FIFO empty or underflow) */
	if (IS_ENABLED(CONFIG_SND_EP93XX_SOC_I2S_WATCHDOG) &&
	    stream == SNDRV_PCM_STREAM_PLAYBACK)
		ep93xx_i2s_write_reg(info, EP93XX_I2S_TXCTRL,
				     EP93XX_I2S_TXCTRL_TXEMPTY_LVL |
				     EP93XX_I2S_TXCTRL_TXUFIE);
}