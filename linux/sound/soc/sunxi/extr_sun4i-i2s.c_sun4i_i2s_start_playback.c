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
struct sun4i_i2s {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUN4I_I2S_CTRL_REG ; 
 int /*<<< orphan*/  SUN4I_I2S_CTRL_TX_EN ; 
 int /*<<< orphan*/  SUN4I_I2S_DMA_INT_CTRL_REG ; 
 int /*<<< orphan*/  SUN4I_I2S_DMA_INT_CTRL_TX_DRQ_EN ; 
 int /*<<< orphan*/  SUN4I_I2S_FIFO_CTRL_FLUSH_TX ; 
 int /*<<< orphan*/  SUN4I_I2S_FIFO_CTRL_REG ; 
 int /*<<< orphan*/  SUN4I_I2S_TX_CNT_REG ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun4i_i2s_start_playback(struct sun4i_i2s *i2s)
{
	/* Flush TX FIFO */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_FIFO_CTRL_REG,
			   SUN4I_I2S_FIFO_CTRL_FLUSH_TX,
			   SUN4I_I2S_FIFO_CTRL_FLUSH_TX);

	/* Clear TX counter */
	regmap_write(i2s->regmap, SUN4I_I2S_TX_CNT_REG, 0);

	/* Enable TX Block */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_CTRL_REG,
			   SUN4I_I2S_CTRL_TX_EN,
			   SUN4I_I2S_CTRL_TX_EN);

	/* Enable TX DRQ */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_DMA_INT_CTRL_REG,
			   SUN4I_I2S_DMA_INT_CTRL_TX_DRQ_EN,
			   SUN4I_I2S_DMA_INT_CTRL_TX_DRQ_EN);
}