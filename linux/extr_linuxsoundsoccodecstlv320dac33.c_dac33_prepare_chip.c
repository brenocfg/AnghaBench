#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct tlv320dac33_priv {int fifo_mode; int burst_bclkdiv; int /*<<< orphan*/  mutex; int /*<<< orphan*/  uthr; int /*<<< orphan*/  alarm_threshold; int /*<<< orphan*/  keep_bclk; int /*<<< orphan*/  chip_power; int /*<<< orphan*/  refclk; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct TYPE_2__ {int rate; int format; } ;

/* Variables and functions */
 unsigned int CALC_OSCSET (int,int /*<<< orphan*/ ) ; 
 unsigned int CALC_RATIOSET (int,int /*<<< orphan*/ ) ; 
 int DAC33_ADJSTEP (int) ; 
 int DAC33_ADJTHRSHLD (int) ; 
 int /*<<< orphan*/  DAC33_ASRC_CTRL_A ; 
 int /*<<< orphan*/  DAC33_ASRC_CTRL_B ; 
 int /*<<< orphan*/  DAC33_ATHR_MSB ; 
 int DAC33_ATM (int /*<<< orphan*/ ) ; 
 int DAC33_BCLKON ; 
 int /*<<< orphan*/  DAC33_CALIB_TIME ; 
 unsigned int DAC33_DACLPDNB ; 
 unsigned int DAC33_DACRPDNB ; 
 int DAC33_FAUTO ; 
 int DAC33_FBYPAS ; 
 int DAC33_FIFOFLUSH ; 
 int /*<<< orphan*/  DAC33_FIFO_CTRL_A ; 
 int /*<<< orphan*/  DAC33_FIFO_IRQ_MODE_A ; 
 int /*<<< orphan*/  DAC33_FIFO_IRQ_MODE_B ; 
 int /*<<< orphan*/  DAC33_FIFO_IRQ_MODE_LEVEL ; 
#define  DAC33_FIFO_MODE1 131 
#define  DAC33_FIFO_MODE7 130 
 int DAC33_INTPM_AHIGH ; 
 int /*<<< orphan*/  DAC33_INTP_CTRL_A ; 
 int /*<<< orphan*/  DAC33_INT_OSC_CTRL ; 
 int /*<<< orphan*/  DAC33_INT_OSC_CTRL_B ; 
 int /*<<< orphan*/  DAC33_INT_OSC_CTRL_C ; 
 int /*<<< orphan*/  DAC33_INT_OSC_FREQ_RAT_A ; 
 int /*<<< orphan*/  DAC33_LTHR_MSB ; 
 int /*<<< orphan*/  DAC33_MODE7_MARGIN ; 
 int DAC33_NCYCL_16 ; 
 int DAC33_NCYCL_32 ; 
 int DAC33_NCYCL_MASK ; 
 unsigned int DAC33_OSCPDNB ; 
 int /*<<< orphan*/  DAC33_PWR_CTRL ; 
 int DAC33_REFDIV (int) ; 
 int /*<<< orphan*/  DAC33_SER_AUDIOIF_CTRL_A ; 
 int /*<<< orphan*/  DAC33_SER_AUDIOIF_CTRL_B ; 
 int /*<<< orphan*/  DAC33_SER_AUDIOIF_CTRL_C ; 
 int DAC33_SRCBYP ; 
 int DAC33_SRCLKDIV (int) ; 
 int /*<<< orphan*/  DAC33_SRC_REF_CLK_RATIO_A ; 
 unsigned int DAC33_THRREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DAC33_UTHR_MSB ; 
 int DAC33_UTM (int /*<<< orphan*/ ) ; 
 int DAC33_WIDTH ; 
 int DAC33_WLEN_16 ; 
 int DAC33_WLEN_24 ; 
 int DAC33_WLEN_MASK ; 
 int EINVAL ; 
#define  SNDRV_PCM_FORMAT_S16_LE 129 
#define  SNDRV_PCM_FORMAT_S32_LE 128 
 int /*<<< orphan*/  dac33_oscwait (struct snd_soc_component*) ; 
 void* dac33_read_reg_cache (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dac33_soft_power (struct snd_soc_component*,int) ; 
 int /*<<< orphan*/  dac33_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dac33_write16 (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tlv320dac33_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int dac33_prepare_chip(struct snd_pcm_substream *substream,
			      struct snd_soc_component *component)
{
	struct tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	unsigned int oscset, ratioset, pwr_ctrl, reg_tmp;
	u8 aictrl_a, aictrl_b, fifoctrl_a;

	switch (substream->runtime->rate) {
	case 44100:
	case 48000:
		oscset = CALC_OSCSET(substream->runtime->rate, dac33->refclk);
		ratioset = CALC_RATIOSET(substream->runtime->rate,
					 dac33->refclk);
		break;
	default:
		dev_err(component->dev, "unsupported rate %d\n",
			substream->runtime->rate);
		return -EINVAL;
	}


	aictrl_a = dac33_read_reg_cache(component, DAC33_SER_AUDIOIF_CTRL_A);
	aictrl_a &= ~(DAC33_NCYCL_MASK | DAC33_WLEN_MASK);
	/* Read FIFO control A, and clear FIFO flush bit */
	fifoctrl_a = dac33_read_reg_cache(component, DAC33_FIFO_CTRL_A);
	fifoctrl_a &= ~DAC33_FIFOFLUSH;

	fifoctrl_a &= ~DAC33_WIDTH;
	switch (substream->runtime->format) {
	case SNDRV_PCM_FORMAT_S16_LE:
		aictrl_a |= (DAC33_NCYCL_16 | DAC33_WLEN_16);
		fifoctrl_a |= DAC33_WIDTH;
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		aictrl_a |= (DAC33_NCYCL_32 | DAC33_WLEN_24);
		break;
	default:
		dev_err(component->dev, "unsupported format %d\n",
			substream->runtime->format);
		return -EINVAL;
	}

	mutex_lock(&dac33->mutex);

	if (!dac33->chip_power) {
		/*
		 * Chip is not powered yet.
		 * Do the init in the dac33_set_bias_level later.
		 */
		mutex_unlock(&dac33->mutex);
		return 0;
	}

	dac33_soft_power(component, 0);
	dac33_soft_power(component, 1);

	reg_tmp = dac33_read_reg_cache(component, DAC33_INT_OSC_CTRL);
	dac33_write(component, DAC33_INT_OSC_CTRL, reg_tmp);

	/* Write registers 0x08 and 0x09 (MSB, LSB) */
	dac33_write16(component, DAC33_INT_OSC_FREQ_RAT_A, oscset);

	/* OSC calibration time */
	dac33_write(component, DAC33_CALIB_TIME, 96);

	/* adjustment treshold & step */
	dac33_write(component, DAC33_INT_OSC_CTRL_B, DAC33_ADJTHRSHLD(2) |
						 DAC33_ADJSTEP(1));

	/* div=4 / gain=1 / div */
	dac33_write(component, DAC33_INT_OSC_CTRL_C, DAC33_REFDIV(4));

	pwr_ctrl = dac33_read_reg_cache(component, DAC33_PWR_CTRL);
	pwr_ctrl |= DAC33_OSCPDNB | DAC33_DACRPDNB | DAC33_DACLPDNB;
	dac33_write(component, DAC33_PWR_CTRL, pwr_ctrl);

	dac33_oscwait(component);

	if (dac33->fifo_mode) {
		/* Generic for all FIFO modes */
		/* 50-51 : ASRC Control registers */
		dac33_write(component, DAC33_ASRC_CTRL_A, DAC33_SRCLKDIV(1));
		dac33_write(component, DAC33_ASRC_CTRL_B, 1); /* ??? */

		/* Write registers 0x34 and 0x35 (MSB, LSB) */
		dac33_write16(component, DAC33_SRC_REF_CLK_RATIO_A, ratioset);

		/* Set interrupts to high active */
		dac33_write(component, DAC33_INTP_CTRL_A, DAC33_INTPM_AHIGH);
	} else {
		/* FIFO bypass mode */
		/* 50-51 : ASRC Control registers */
		dac33_write(component, DAC33_ASRC_CTRL_A, DAC33_SRCBYP);
		dac33_write(component, DAC33_ASRC_CTRL_B, 0); /* ??? */
	}

	/* Interrupt behaviour configuration */
	switch (dac33->fifo_mode) {
	case DAC33_FIFO_MODE1:
		dac33_write(component, DAC33_FIFO_IRQ_MODE_B,
			    DAC33_ATM(DAC33_FIFO_IRQ_MODE_LEVEL));
		break;
	case DAC33_FIFO_MODE7:
		dac33_write(component, DAC33_FIFO_IRQ_MODE_A,
			DAC33_UTM(DAC33_FIFO_IRQ_MODE_LEVEL));
		break;
	default:
		/* in FIFO bypass mode, the interrupts are not used */
		break;
	}

	aictrl_b = dac33_read_reg_cache(component, DAC33_SER_AUDIOIF_CTRL_B);

	switch (dac33->fifo_mode) {
	case DAC33_FIFO_MODE1:
		/*
		 * For mode1:
		 * Disable the FIFO bypass (Enable the use of FIFO)
		 * Select nSample mode
		 * BCLK is only running when data is needed by DAC33
		 */
		fifoctrl_a &= ~DAC33_FBYPAS;
		fifoctrl_a &= ~DAC33_FAUTO;
		if (dac33->keep_bclk)
			aictrl_b |= DAC33_BCLKON;
		else
			aictrl_b &= ~DAC33_BCLKON;
		break;
	case DAC33_FIFO_MODE7:
		/*
		 * For mode1:
		 * Disable the FIFO bypass (Enable the use of FIFO)
		 * Select Threshold mode
		 * BCLK is only running when data is needed by DAC33
		 */
		fifoctrl_a &= ~DAC33_FBYPAS;
		fifoctrl_a |= DAC33_FAUTO;
		if (dac33->keep_bclk)
			aictrl_b |= DAC33_BCLKON;
		else
			aictrl_b &= ~DAC33_BCLKON;
		break;
	default:
		/*
		 * For FIFO bypass mode:
		 * Enable the FIFO bypass (Disable the FIFO use)
		 * Set the BCLK as continuous
		 */
		fifoctrl_a |= DAC33_FBYPAS;
		aictrl_b |= DAC33_BCLKON;
		break;
	}

	dac33_write(component, DAC33_FIFO_CTRL_A, fifoctrl_a);
	dac33_write(component, DAC33_SER_AUDIOIF_CTRL_A, aictrl_a);
	dac33_write(component, DAC33_SER_AUDIOIF_CTRL_B, aictrl_b);

	/*
	 * BCLK divide ratio
	 * 0: 1.5
	 * 1: 1
	 * 2: 2
	 * ...
	 * 254: 254
	 * 255: 255
	 */
	if (dac33->fifo_mode)
		dac33_write(component, DAC33_SER_AUDIOIF_CTRL_C,
							dac33->burst_bclkdiv);
	else
		if (substream->runtime->format == SNDRV_PCM_FORMAT_S16_LE)
			dac33_write(component, DAC33_SER_AUDIOIF_CTRL_C, 32);
		else
			dac33_write(component, DAC33_SER_AUDIOIF_CTRL_C, 16);

	switch (dac33->fifo_mode) {
	case DAC33_FIFO_MODE1:
		dac33_write16(component, DAC33_ATHR_MSB,
			      DAC33_THRREG(dac33->alarm_threshold));
		break;
	case DAC33_FIFO_MODE7:
		/*
		 * Configure the threshold levels, and leave 10 sample space
		 * at the bottom, and also at the top of the FIFO
		 */
		dac33_write16(component, DAC33_UTHR_MSB, DAC33_THRREG(dac33->uthr));
		dac33_write16(component, DAC33_LTHR_MSB,
			      DAC33_THRREG(DAC33_MODE7_MARGIN));
		break;
	default:
		break;
	}

	mutex_unlock(&dac33->mutex);

	return 0;
}