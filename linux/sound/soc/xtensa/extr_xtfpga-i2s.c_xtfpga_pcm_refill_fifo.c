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
struct xtfpga_i2s {int /*<<< orphan*/  regmap; int /*<<< orphan*/  tx_fifo_low; int /*<<< orphan*/  tx_fifo_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  XTFPGA_I2S_CONFIG ; 
 int XTFPGA_I2S_CONFIG_INT_ENABLE ; 
 int XTFPGA_I2S_CONFIG_TX_ENABLE ; 
 unsigned int XTFPGA_I2S_INT_LEVEL ; 
 int /*<<< orphan*/  XTFPGA_I2S_INT_MASK ; 
 int /*<<< orphan*/  XTFPGA_I2S_INT_STATUS ; 
 unsigned int XTFPGA_I2S_INT_UNDERRUN ; 
 unsigned int XTFPGA_I2S_INT_VALID ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int xtfpga_pcm_push_tx (struct xtfpga_i2s*) ; 

__attribute__((used)) static void xtfpga_pcm_refill_fifo(struct xtfpga_i2s *i2s)
{
	unsigned int_status;
	unsigned i;

	regmap_read(i2s->regmap, XTFPGA_I2S_INT_STATUS,
		    &int_status);

	for (i = 0; i < 2; ++i) {
		bool tx_active = xtfpga_pcm_push_tx(i2s);

		regmap_write(i2s->regmap, XTFPGA_I2S_INT_STATUS,
			     XTFPGA_I2S_INT_VALID);
		if (tx_active)
			regmap_read(i2s->regmap, XTFPGA_I2S_INT_STATUS,
				    &int_status);

		if (!tx_active ||
		    !(int_status & XTFPGA_I2S_INT_LEVEL))
			break;

		/* After the push the level IRQ is still asserted,
		 * means FIFO level is below tx_fifo_low. Estimate
		 * it as tx_fifo_low.
		 */
		i2s->tx_fifo_level = i2s->tx_fifo_low;
	}

	if (!(int_status & XTFPGA_I2S_INT_LEVEL))
		regmap_write(i2s->regmap, XTFPGA_I2S_INT_MASK,
			     XTFPGA_I2S_INT_VALID);
	else if (!(int_status & XTFPGA_I2S_INT_UNDERRUN))
		regmap_write(i2s->regmap, XTFPGA_I2S_INT_MASK,
			     XTFPGA_I2S_INT_UNDERRUN);

	if (!(int_status & XTFPGA_I2S_INT_UNDERRUN))
		regmap_update_bits(i2s->regmap, XTFPGA_I2S_CONFIG,
				   XTFPGA_I2S_CONFIG_INT_ENABLE |
				   XTFPGA_I2S_CONFIG_TX_ENABLE,
				   XTFPGA_I2S_CONFIG_INT_ENABLE |
				   XTFPGA_I2S_CONFIG_TX_ENABLE);
	else
		regmap_update_bits(i2s->regmap, XTFPGA_I2S_CONFIG,
				   XTFPGA_I2S_CONFIG_INT_ENABLE |
				   XTFPGA_I2S_CONFIG_TX_ENABLE, 0);
}