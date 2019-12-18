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
struct davinci_mcasp {int tdm_slots; int* tdm_mask; int /*<<< orphan*/  channels; int /*<<< orphan*/  dat_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAVINCI_MCASP_ACLKXCTL_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_RXFMCTL_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_RXFMT_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_RXTDM_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_TXFMCTL_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_TXFMT_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_TXTDM_REG ; 
 int /*<<< orphan*/  FSRMOD (int) ; 
 int /*<<< orphan*/  FSXMOD (int) ; 
 int RXORD ; 
 int SNDRV_PCM_STREAM_CAPTURE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int TXORD ; 
 int TXSEL ; 
 int /*<<< orphan*/  TX_ASYNC ; 
 int hweight32 (int) ; 
 int /*<<< orphan*/  mcasp_clr_bits (struct davinci_mcasp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mcasp_is_synchronous (struct davinci_mcasp*) ; 
 int /*<<< orphan*/  mcasp_mod_bits (struct davinci_mcasp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcasp_set_bits (struct davinci_mcasp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mcasp_set_reg (struct davinci_mcasp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mcasp_i2s_hw_param(struct davinci_mcasp *mcasp, int stream,
			      int channels)
{
	int i, active_slots;
	int total_slots;
	int active_serializers;
	u32 mask = 0;
	u32 busel = 0;

	total_slots = mcasp->tdm_slots;

	/*
	 * If more than one serializer is needed, then use them with
	 * all the specified tdm_slots. Otherwise, one serializer can
	 * cope with the transaction using just as many slots as there
	 * are channels in the stream.
	 */
	if (mcasp->tdm_mask[stream]) {
		active_slots = hweight32(mcasp->tdm_mask[stream]);
		active_serializers = (channels + active_slots - 1) /
			active_slots;
		if (active_serializers == 1)
			active_slots = channels;
		for (i = 0; i < total_slots; i++) {
			if ((1 << i) & mcasp->tdm_mask[stream]) {
				mask |= (1 << i);
				if (--active_slots <= 0)
					break;
			}
		}
	} else {
		active_serializers = (channels + total_slots - 1) / total_slots;
		if (active_serializers == 1)
			active_slots = channels;
		else
			active_slots = total_slots;

		for (i = 0; i < active_slots; i++)
			mask |= (1 << i);
	}

	mcasp_clr_bits(mcasp, DAVINCI_MCASP_ACLKXCTL_REG, TX_ASYNC);

	if (!mcasp->dat_port)
		busel = TXSEL;

	if (stream == SNDRV_PCM_STREAM_PLAYBACK) {
		mcasp_set_reg(mcasp, DAVINCI_MCASP_TXTDM_REG, mask);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_TXFMT_REG, busel | TXORD);
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG,
			       FSXMOD(total_slots), FSXMOD(0x1FF));
	} else if (stream == SNDRV_PCM_STREAM_CAPTURE) {
		mcasp_set_reg(mcasp, DAVINCI_MCASP_RXTDM_REG, mask);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_RXFMT_REG, busel | RXORD);
		mcasp_mod_bits(mcasp, DAVINCI_MCASP_RXFMCTL_REG,
			       FSRMOD(total_slots), FSRMOD(0x1FF));
		/*
		 * If McASP is set to be TX/RX synchronous and the playback is
		 * not running already we need to configure the TX slots in
		 * order to have correct FSX on the bus
		 */
		if (mcasp_is_synchronous(mcasp) && !mcasp->channels)
			mcasp_mod_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG,
				       FSXMOD(total_slots), FSXMOD(0x1FF));
	}

	return 0;
}