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
struct davinci_mcasp {int slot_width; scalar_t__ op_mode; } ;

/* Variables and functions */
 scalar_t__ DAVINCI_MCASP_DIT_MODE ; 
 int /*<<< orphan*/  DAVINCI_MCASP_RXFMT_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_RXMASK_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_TXFMT_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_TXMASK_REG ; 
 int /*<<< orphan*/  RXROT (int) ; 
 int /*<<< orphan*/  RXSSZ (int) ; 
 int /*<<< orphan*/  TXROT (int) ; 
 int /*<<< orphan*/  TXSSZ (int) ; 
 int /*<<< orphan*/  mcasp_mod_bits (struct davinci_mcasp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcasp_set_reg (struct davinci_mcasp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int davinci_config_channel_size(struct davinci_mcasp *mcasp,
				       int sample_width)
{
	u32 fmt;
	u32 tx_rotate = (sample_width / 4) & 0x7;
	u32 mask = (1ULL << sample_width) - 1;
	u32 slot_width = sample_width;

	/*
	 * For captured data we should not rotate, inversion and masking is
	 * enoguh to get the data to the right position:
	 * Format	  data from bus		after reverse (XRBUF)
	 * S16_LE:	|LSB|MSB|xxx|xxx|	|xxx|xxx|MSB|LSB|
	 * S24_3LE:	|LSB|DAT|MSB|xxx|	|xxx|MSB|DAT|LSB|
	 * S24_LE:	|LSB|DAT|MSB|xxx|	|xxx|MSB|DAT|LSB|
	 * S32_LE:	|LSB|DAT|DAT|MSB|	|MSB|DAT|DAT|LSB|
	 */
	u32 rx_rotate = 0;

	/*
	 * Setting the tdm slot width either with set_clkdiv() or
	 * set_tdm_slot() allows us to for example send 32 bits per
	 * channel to the codec, while only 16 of them carry audio
	 * payload.
	 */
	if (mcasp->slot_width) {
		/*
		 * When we have more bclk then it is needed for the
		 * data, we need to use the rotation to move the
		 * received samples to have correct alignment.
		 */
		slot_width = mcasp->slot_width;
		rx_rotate = (slot_width - sample_width) / 4;
	}

	/* mapping of the XSSZ bit-field as described in the datasheet */
	fmt = (slot_width >> 1) - 1;

	if (mcasp->op_mode != DAVINCI_MCASP_DIT_MODE) {
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_RXFMT_REG, RXSSZ(fmt),
			       RXSSZ(0x0F));
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_TXFMT_REG, TXSSZ(fmt),
			       TXSSZ(0x0F));
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_TXFMT_REG, TXROT(tx_rotate),
			       TXROT(7));
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_RXFMT_REG, RXROT(rx_rotate),
			       RXROT(7));
		mcasp_set_reg(mcasp, DAVINCI_MCASP_RXMASK_REG, mask);
	}

	mcasp_set_reg(mcasp, DAVINCI_MCASP_TXMASK_REG, mask);

	return 0;
}