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
struct davinci_mcasp {int tdm_slots; scalar_t__ version; int num_serializer; scalar_t__* serial_dir; int txnumevt; int rxnumevt; int /*<<< orphan*/  dev; scalar_t__ fifo_base; struct snd_dmaengine_dai_dma_data* dma_data; } ;

/* Variables and functions */
 scalar_t__ AXR (int) ; 
 scalar_t__ DAVINCI_MCASP_PDIR_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_PFUNC_REG ; 
 scalar_t__ DAVINCI_MCASP_PWREMUMGT_REG ; 
 scalar_t__ DAVINCI_MCASP_REVTCTL_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_RXSTAT_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_TXSTAT_REG ; 
 scalar_t__ DAVINCI_MCASP_XEVTCTL_REG ; 
 scalar_t__ DAVINCI_MCASP_XRSRCTL_REG (int) ; 
 int DISMOD_LOW ; 
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
 scalar_t__ RXDATADMADIS ; 
 scalar_t__ RX_MODE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int SRMOD_INACTIVE ; 
 int /*<<< orphan*/  SRMOD_MASK ; 
 scalar_t__ TXDATADMADIS ; 
 scalar_t__ TX_MODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  mcasp_clr_bits (struct davinci_mcasp*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mcasp_mod_bits (struct davinci_mcasp*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcasp_set_bits (struct davinci_mcasp*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mcasp_set_reg (struct davinci_mcasp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mcasp_common_hw_param(struct davinci_mcasp *mcasp, int stream,
				 int period_words, int channels)
{
	struct snd_dmaengine_dai_dma_data *dma_data = &mcasp->dma_data[stream];
	int i;
	u8 tx_ser = 0;
	u8 rx_ser = 0;
	u8 slots = mcasp->tdm_slots;
	u8 max_active_serializers = (channels + slots - 1) / slots;
	int active_serializers, numevt;
	u32 reg;
	/* Default configuration */
	if (mcasp->version < MCASP_VERSION_3)
		mcasp_set_bits(mcasp, DAVINCI_MCASP_PWREMUMGT_REG, MCASP_SOFT);

	/* All PINS as McASP */
	mcasp_set_reg(mcasp, DAVINCI_MCASP_PFUNC_REG, 0x00000000);

	if (stream == SNDRV_PCM_STREAM_PLAYBACK) {
		mcasp_set_reg(mcasp, DAVINCI_MCASP_TXSTAT_REG, 0xFFFFFFFF);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_XEVTCTL_REG, TXDATADMADIS);
	} else {
		mcasp_set_reg(mcasp, DAVINCI_MCASP_RXSTAT_REG, 0xFFFFFFFF);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_REVTCTL_REG, RXDATADMADIS);
	}

	for (i = 0; i < mcasp->num_serializer; i++) {
		mcasp_set_bits(mcasp, DAVINCI_MCASP_XRSRCTL_REG(i),
			       mcasp->serial_dir[i]);
		if (mcasp->serial_dir[i] == TX_MODE &&
					tx_ser < max_active_serializers) {
			mcasp_set_bits(mcasp, DAVINCI_MCASP_PDIR_REG, AXR(i));
			mcasp_mod_bits(mcasp, DAVINCI_MCASP_XRSRCTL_REG(i),
				       DISMOD_LOW, DISMOD_MASK);
			tx_ser++;
		} else if (mcasp->serial_dir[i] == RX_MODE &&
					rx_ser < max_active_serializers) {
			mcasp_clr_bits(mcasp, DAVINCI_MCASP_PDIR_REG, AXR(i));
			rx_ser++;
		} else if (mcasp->serial_dir[i] == INACTIVE_MODE) {
			mcasp_mod_bits(mcasp, DAVINCI_MCASP_XRSRCTL_REG(i),
				       SRMOD_INACTIVE, SRMOD_MASK);
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
		return 0;
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

	return 0;
}