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
typedef  int uint32_t ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct bcm2835_i2s_dev {int tdm_slots; unsigned int slot_width; int frame_length; unsigned int rx_mask; unsigned int tx_mask; int fmt; int clk_rate; int /*<<< orphan*/  dev; int /*<<< orphan*/  i2s_regmap; int /*<<< orphan*/  clk; scalar_t__ clk_prepared; } ;

/* Variables and functions */
 unsigned int BCM2835_I2S_CH1 (unsigned int) ; 
 unsigned int BCM2835_I2S_CH1_POS (unsigned int) ; 
 unsigned int BCM2835_I2S_CH2 (unsigned int) ; 
 unsigned int BCM2835_I2S_CH2_POS (unsigned int) ; 
 unsigned int BCM2835_I2S_CHEN ; 
 unsigned int BCM2835_I2S_CHWEX ; 
 unsigned int BCM2835_I2S_CHWID (unsigned int) ; 
 unsigned int BCM2835_I2S_CLKI ; 
 unsigned int BCM2835_I2S_CLKM ; 
 int /*<<< orphan*/  BCM2835_I2S_CS_A_REG ; 
 int BCM2835_I2S_DMAEN ; 
 int /*<<< orphan*/  BCM2835_I2S_DREQ_A_REG ; 
 unsigned int BCM2835_I2S_FLEN (int) ; 
 unsigned int BCM2835_I2S_FRXP ; 
 unsigned int BCM2835_I2S_FSI ; 
 unsigned int BCM2835_I2S_FSLEN (unsigned int) ; 
 unsigned int BCM2835_I2S_FSM ; 
 unsigned int BCM2835_I2S_FTXP ; 
 int /*<<< orphan*/  BCM2835_I2S_MODE_A_REG ; 
 int BCM2835_I2S_RX (int) ; 
 int /*<<< orphan*/  BCM2835_I2S_RXC_A_REG ; 
 int BCM2835_I2S_RXON ; 
 int BCM2835_I2S_RXTHR (int) ; 
 int BCM2835_I2S_RX_PANIC (int) ; 
 int BCM2835_I2S_TX (int) ; 
 int /*<<< orphan*/  BCM2835_I2S_TXC_A_REG ; 
 int BCM2835_I2S_TXON ; 
 int BCM2835_I2S_TXTHR (int) ; 
 int BCM2835_I2S_TX_PANIC (int) ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 140 
#define  SND_SOC_DAIFMT_CBM_CFS 139 
#define  SND_SOC_DAIFMT_CBS_CFM 138 
#define  SND_SOC_DAIFMT_CBS_CFS 137 
#define  SND_SOC_DAIFMT_DSP_A 136 
#define  SND_SOC_DAIFMT_DSP_B 135 
 int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 134 
#define  SND_SOC_DAIFMT_IB_IF 133 
#define  SND_SOC_DAIFMT_IB_NF 132 
 int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 131 
 int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 130 
#define  SND_SOC_DAIFMT_NB_NF 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  bcm2835_i2s_calc_channel_pos (unsigned int*,unsigned int*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  bcm2835_i2s_clear_fifos (struct bcm2835_i2s_dev*,int,int) ; 
 int /*<<< orphan*/  bcm2835_i2s_start_clock (struct bcm2835_i2s_dev*) ; 
 int /*<<< orphan*/  bcm2835_i2s_stop_clock (struct bcm2835_i2s_dev*) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 unsigned int params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct bcm2835_i2s_dev* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int snd_soc_params_to_bclk (struct snd_pcm_hw_params*) ; 
 int snd_soc_params_to_frame_size (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int bcm2835_i2s_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *params,
				 struct snd_soc_dai *dai)
{
	struct bcm2835_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);
	unsigned int data_length, data_delay, framesync_length;
	unsigned int slots, slot_width, odd_slot_offset;
	int frame_length, bclk_rate;
	unsigned int rx_mask, tx_mask;
	unsigned int rx_ch1_pos, rx_ch2_pos, tx_ch1_pos, tx_ch2_pos;
	unsigned int mode, format;
	bool bit_clock_master = false;
	bool frame_sync_master = false;
	bool frame_start_falling_edge = false;
	uint32_t csreg;
	int ret = 0;

	/*
	 * If a stream is already enabled,
	 * the registers are already set properly.
	 */
	regmap_read(dev->i2s_regmap, BCM2835_I2S_CS_A_REG, &csreg);

	if (csreg & (BCM2835_I2S_TXON | BCM2835_I2S_RXON))
		return 0;

	data_length = params_width(params);
	data_delay = 0;
	odd_slot_offset = 0;
	mode = 0;

	if (dev->tdm_slots) {
		slots = dev->tdm_slots;
		slot_width = dev->slot_width;
		frame_length = dev->frame_length;
		rx_mask = dev->rx_mask;
		tx_mask = dev->tx_mask;
		bclk_rate = dev->frame_length * params_rate(params);
	} else {
		slots = 2;
		slot_width = params_width(params);
		rx_mask = 0x03;
		tx_mask = 0x03;

		frame_length = snd_soc_params_to_frame_size(params);
		if (frame_length < 0)
			return frame_length;

		bclk_rate = snd_soc_params_to_bclk(params);
		if (bclk_rate < 0)
			return bclk_rate;
	}

	/* Check if data fits into slots */
	if (data_length > slot_width)
		return -EINVAL;

	/* Check if CPU is bit clock master */
	switch (dev->fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
	case SND_SOC_DAIFMT_CBS_CFM:
		bit_clock_master = true;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
	case SND_SOC_DAIFMT_CBM_CFM:
		bit_clock_master = false;
		break;
	default:
		return -EINVAL;
	}

	/* Check if CPU is frame sync master */
	switch (dev->fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
	case SND_SOC_DAIFMT_CBM_CFS:
		frame_sync_master = true;
		break;
	case SND_SOC_DAIFMT_CBS_CFM:
	case SND_SOC_DAIFMT_CBM_CFM:
		frame_sync_master = false;
		break;
	default:
		return -EINVAL;
	}

	/* Clock should only be set up here if CPU is clock master */
	if (bit_clock_master &&
	    (!dev->clk_prepared || dev->clk_rate != bclk_rate)) {
		if (dev->clk_prepared)
			bcm2835_i2s_stop_clock(dev);

		if (dev->clk_rate != bclk_rate) {
			ret = clk_set_rate(dev->clk, bclk_rate);
			if (ret)
				return ret;
			dev->clk_rate = bclk_rate;
		}

		bcm2835_i2s_start_clock(dev);
	}

	/* Setup the frame format */
	format = BCM2835_I2S_CHEN;

	if (data_length >= 24)
		format |= BCM2835_I2S_CHWEX;

	format |= BCM2835_I2S_CHWID((data_length-8)&0xf);

	/* CH2 format is the same as for CH1 */
	format = BCM2835_I2S_CH1(format) | BCM2835_I2S_CH2(format);

	switch (dev->fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		/* I2S mode needs an even number of slots */
		if (slots & 1)
			return -EINVAL;

		/*
		 * Use I2S-style logical slot numbering: even slots
		 * are in first half of frame, odd slots in second half.
		 */
		odd_slot_offset = slots >> 1;

		/* MSB starts one cycle after frame start */
		data_delay = 1;

		/* Setup frame sync signal for 50% duty cycle */
		framesync_length = frame_length / 2;
		frame_start_falling_edge = true;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		if (slots & 1)
			return -EINVAL;

		odd_slot_offset = slots >> 1;
		data_delay = 0;
		framesync_length = frame_length / 2;
		frame_start_falling_edge = false;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		if (slots & 1)
			return -EINVAL;

		/* Odd frame lengths aren't supported */
		if (frame_length & 1)
			return -EINVAL;

		odd_slot_offset = slots >> 1;
		data_delay = slot_width - data_length;
		framesync_length = frame_length / 2;
		frame_start_falling_edge = false;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		data_delay = 1;
		framesync_length = 1;
		frame_start_falling_edge = false;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		data_delay = 0;
		framesync_length = 1;
		frame_start_falling_edge = false;
		break;
	default:
		return -EINVAL;
	}

	bcm2835_i2s_calc_channel_pos(&rx_ch1_pos, &rx_ch2_pos,
		rx_mask, slot_width, data_delay, odd_slot_offset);
	bcm2835_i2s_calc_channel_pos(&tx_ch1_pos, &tx_ch2_pos,
		tx_mask, slot_width, data_delay, odd_slot_offset);

	/*
	 * Transmitting data immediately after frame start, eg
	 * in left-justified or DSP mode A, only works stable
	 * if bcm2835 is the frame clock master.
	 */
	if ((!rx_ch1_pos || !tx_ch1_pos) && !frame_sync_master)
		dev_warn(dev->dev,
			"Unstable slave config detected, L/R may be swapped");

	/*
	 * Set format for both streams.
	 * We cannot set another frame length
	 * (and therefore word length) anyway,
	 * so the format will be the same.
	 */
	regmap_write(dev->i2s_regmap, BCM2835_I2S_RXC_A_REG, 
		  format
		| BCM2835_I2S_CH1_POS(rx_ch1_pos)
		| BCM2835_I2S_CH2_POS(rx_ch2_pos));
	regmap_write(dev->i2s_regmap, BCM2835_I2S_TXC_A_REG, 
		  format
		| BCM2835_I2S_CH1_POS(tx_ch1_pos)
		| BCM2835_I2S_CH2_POS(tx_ch2_pos));

	/* Setup the I2S mode */

	if (data_length <= 16) {
		/*
		 * Use frame packed mode (2 channels per 32 bit word)
		 * We cannot set another frame length in the second stream
		 * (and therefore word length) anyway,
		 * so the format will be the same.
		 */
		mode |= BCM2835_I2S_FTXP | BCM2835_I2S_FRXP;
	}

	mode |= BCM2835_I2S_FLEN(frame_length - 1);
	mode |= BCM2835_I2S_FSLEN(framesync_length);

	/* CLKM selects bcm2835 clock slave mode */
	if (!bit_clock_master)
		mode |= BCM2835_I2S_CLKM;

	/* FSM selects bcm2835 frame sync slave mode */
	if (!frame_sync_master)
		mode |= BCM2835_I2S_FSM;

	/* CLKI selects normal clocking mode, sampling on rising edge */
        switch (dev->fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
	case SND_SOC_DAIFMT_NB_IF:
		mode |= BCM2835_I2S_CLKI;
		break;
	case SND_SOC_DAIFMT_IB_NF:
	case SND_SOC_DAIFMT_IB_IF:
		break;
	default:
		return -EINVAL;
	}

	/* FSI selects frame start on falling edge */
	switch (dev->fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
	case SND_SOC_DAIFMT_IB_NF:
		if (frame_start_falling_edge)
			mode |= BCM2835_I2S_FSI;
		break;
	case SND_SOC_DAIFMT_NB_IF:
	case SND_SOC_DAIFMT_IB_IF:
		if (!frame_start_falling_edge)
			mode |= BCM2835_I2S_FSI;
		break;
	default:
		return -EINVAL;
	}

	regmap_write(dev->i2s_regmap, BCM2835_I2S_MODE_A_REG, mode);

	/* Setup the DMA parameters */
	regmap_update_bits(dev->i2s_regmap, BCM2835_I2S_CS_A_REG,
			BCM2835_I2S_RXTHR(1)
			| BCM2835_I2S_TXTHR(1)
			| BCM2835_I2S_DMAEN, 0xffffffff);

	regmap_update_bits(dev->i2s_regmap, BCM2835_I2S_DREQ_A_REG,
			  BCM2835_I2S_TX_PANIC(0x10)
			| BCM2835_I2S_RX_PANIC(0x30)
			| BCM2835_I2S_TX(0x30)
			| BCM2835_I2S_RX(0x20), 0xffffffff);

	/* Clear FIFOs */
	bcm2835_i2s_clear_fifos(dev, true, true);

	dev_dbg(dev->dev,
		"slots: %d width: %d rx mask: 0x%02x tx_mask: 0x%02x\n",
		slots, slot_width, rx_mask, tx_mask);

	dev_dbg(dev->dev, "frame len: %d sync len: %d data len: %d\n",
		frame_length, framesync_length, data_length);

	dev_dbg(dev->dev, "rx pos: %d,%d tx pos: %d,%d\n",
		rx_ch1_pos, rx_ch2_pos, tx_ch1_pos, tx_ch2_pos);

	dev_dbg(dev->dev, "sampling rate: %d bclk rate: %d\n",
		params_rate(params), bclk_rate);

	dev_dbg(dev->dev, "CLKM: %d CLKI: %d FSM: %d FSI: %d frame start: %s edge\n",
		!!(mode & BCM2835_I2S_CLKM),
		!!(mode & BCM2835_I2S_CLKI),
		!!(mode & BCM2835_I2S_FSM),
		!!(mode & BCM2835_I2S_FSI),
		(mode & BCM2835_I2S_FSI) ? "falling" : "rising");

	return ret;
}