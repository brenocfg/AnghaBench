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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct snd_dmaengine_dai_dma_data {int maxburst; } ;
struct davinci_mcasp {int tdm_slots; scalar_t__ version; int* active_serializers; int num_serializer; scalar_t__* serial_dir; int dismod; int txnumevt; int rxnumevt; int /*<<< orphan*/  dev; scalar_t__ fifo_base; int /*<<< orphan*/  pdir; struct snd_dmaengine_dai_dma_data* dma_data; } ;

/* Variables and functions */
 scalar_t__ DAVINCI_MCASP_PWREMUMGT_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_REVTCTL_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_RXSTAT_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_TXSTAT_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_XEVTCTL_REG ; 
 scalar_t__ DAVINCI_MCASP_XRSRCTL_REG (int) ; 
 int /*<<< orphan*/  DISMOD_MASK ; 
 int EINVAL ; 
 scalar_t__ INACTIVE_MODE ; 
 scalar_t__ MCASP_RFIFOCTL_OFFSET ; 
 scalar_t__ MCASP_SOFT ; 
 scalar_t__ MCASP_VERSION_3 ; 
 scalar_t__ MCASP_WFIFOCTL_OFFSET ; 
 int /*<<< orphan*/  NUMDMA_MASK ; 
 int NUMEVT (int) ; 
 int /*<<< orphan*/  NUMEVT_MASK ; 
 int /*<<< orphan*/  PIN_BIT_AXR (int) ; 
 int /*<<< orphan*/  RXDATADMADIS ; 
 scalar_t__ RX_MODE ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int SRMOD_INACTIVE ; 
 int /*<<< orphan*/  SRMOD_MASK ; 
 int /*<<< orphan*/  TXDATADMADIS ; 
 scalar_t__ TX_MODE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  mcasp_clr_bits (struct davinci_mcasp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcasp_mod_bits (struct davinci_mcasp*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcasp_set_bits (struct davinci_mcasp*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mcasp_set_reg (struct davinci_mcasp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mcasp_common_hw_param(struct davinci_mcasp *mcasp, int stream,
				 int period_words, int channels)
{
	struct snd_dmaengine_dai_dma_data *dma_data = &mcasp->dma_data[stream];
	int i;
	u8 tx_ser = 0;
	u8 rx_ser = 0;
	u8 slots = mcasp->tdm_slots;
	u8 max_active_serializers = (channels + slots - 1) / slots;
	u8 max_rx_serializers, max_tx_serializers;
	int active_serializers, numevt;
	u32 reg;
	/* Default configuration */
	if (mcasp->version < MCASP_VERSION_3)
		mcasp_set_bits(mcasp, DAVINCI_MCASP_PWREMUMGT_REG, MCASP_SOFT);

	if (stream == SNDRV_PCM_STREAM_PLAYBACK) {
		mcasp_set_reg(mcasp, DAVINCI_MCASP_TXSTAT_REG, 0xFFFFFFFF);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_XEVTCTL_REG, TXDATADMADIS);
		max_tx_serializers = max_active_serializers;
		max_rx_serializers =
			mcasp->active_serializers[SNDRV_PCM_STREAM_CAPTURE];
	} else {
		mcasp_set_reg(mcasp, DAVINCI_MCASP_RXSTAT_REG, 0xFFFFFFFF);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_REVTCTL_REG, RXDATADMADIS);
		max_tx_serializers =
			mcasp->active_serializers[SNDRV_PCM_STREAM_PLAYBACK];
		max_rx_serializers = max_active_serializers;
	}

	for (i = 0; i < mcasp->num_serializer; i++) {
		mcasp_set_bits(mcasp, DAVINCI_MCASP_XRSRCTL_REG(i),
			       mcasp->serial_dir[i]);
		if (mcasp->serial_dir[i] == TX_MODE &&
					tx_ser < max_tx_serializers) {
			mcasp_mod_bits(mcasp, DAVINCI_MCASP_XRSRCTL_REG(i),
				       mcasp->dismod, DISMOD_MASK);
			set_bit(PIN_BIT_AXR(i), &mcasp->pdir);
			tx_ser++;
		} else if (mcasp->serial_dir[i] == RX_MODE &&
					rx_ser < max_rx_serializers) {
			clear_bit(PIN_BIT_AXR(i), &mcasp->pdir);
			rx_ser++;
		} else {
			/* Inactive or unused pin, set it to inactive */
			mcasp_mod_bits(mcasp, DAVINCI_MCASP_XRSRCTL_REG(i),
				       SRMOD_INACTIVE, SRMOD_MASK);
			/* If unused, set DISMOD for the pin */
			if (mcasp->serial_dir[i] != INACTIVE_MODE)
				mcasp_mod_bits(mcasp,
					       DAVINCI_MCASP_XRSRCTL_REG(i),
					       mcasp->dismod, DISMOD_MASK);
			clear_bit(PIN_BIT_AXR(i), &mcasp->pdir);
		}
	}

	if (stream == SNDRV_PCM_STREAM_PLAYBACK) {
		active_serializers = tx_ser;
		numevt = mcasp->txnumevt;
		reg = mcasp->fifo_base + MCASP_WFIFOCTL_OFFSET;
	} else {
		active_serializers = rx_ser;
		numevt = mcasp->rxnumevt;
		reg = mcasp->fifo_base + MCASP_RFIFOCTL_OFFSET;
	}

	if (active_serializers < max_active_serializers) {
		dev_warn(mcasp->dev, "stream has more channels (%d) than are "
			 "enabled in mcasp (%d)\n", channels,
			 active_serializers * slots);
		return -EINVAL;
	}

	/* AFIFO is not in use */
	if (!numevt) {
		/* Configure the burst size for platform drivers */
		if (active_serializers > 1) {
			/*
			 * If more than one serializers are in use we have one
			 * DMA request to provide data for all serializers.
			 * For example if three serializers are enabled the DMA
			 * need to transfer three words per DMA request.
			 */
			dma_data->maxburst = active_serializers;
		} else {
			dma_data->maxburst = 0;
		}

		goto out;
	}

	if (period_words % active_serializers) {
		dev_err(mcasp->dev, "Invalid combination of period words and "
			"active serializers: %d, %d\n", period_words,
			active_serializers);
		return -EINVAL;
	}

	/*
	 * Calculate the optimal AFIFO depth for platform side:
	 * The number of words for numevt need to be in steps of active
	 * serializers.
	 */
	numevt = (numevt / active_serializers) * active_serializers;

	while (period_words % numevt && numevt > 0)
		numevt -= active_serializers;
	if (numevt <= 0)
		numevt = active_serializers;

	mcasp_mod_bits(mcasp, reg, active_serializers, NUMDMA_MASK);
	mcasp_mod_bits(mcasp, reg, NUMEVT(numevt), NUMEVT_MASK);

	/* Configure the burst size for platform drivers */
	if (numevt == 1)
		numevt = 0;
	dma_data->maxburst = numevt;

out:
	mcasp->active_serializers[stream] = active_serializers;

	return 0;
}