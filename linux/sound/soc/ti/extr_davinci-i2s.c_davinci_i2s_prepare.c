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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct davinci_mcbsp_dev {int pcr; } ;

/* Variables and functions */
 int DAVINCI_MCBSP_PCR_CLKRM ; 
 int DAVINCI_MCBSP_PCR_CLKXM ; 
 int DAVINCI_MCBSP_PCR_FSRM ; 
 int DAVINCI_MCBSP_PCR_FSXM ; 
 int DAVINCI_MCBSP_SPCR_GRST ; 
 int /*<<< orphan*/  DAVINCI_MCBSP_SPCR_REG ; 
 int DAVINCI_MCBSP_SPCR_RRST ; 
 int DAVINCI_MCBSP_SPCR_XRST ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int davinci_mcbsp_read_reg (struct davinci_mcbsp_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  davinci_mcbsp_stop (struct davinci_mcbsp_dev*,int) ; 
 int /*<<< orphan*/  davinci_mcbsp_write_reg (struct davinci_mcbsp_dev*,int /*<<< orphan*/ ,int) ; 
 struct davinci_mcbsp_dev* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  toggle_clock (struct davinci_mcbsp_dev*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int davinci_i2s_prepare(struct snd_pcm_substream *substream,
		struct snd_soc_dai *dai)
{
	struct davinci_mcbsp_dev *dev = snd_soc_dai_get_drvdata(dai);
	int playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	u32 spcr;
	u32 mask = playback ? DAVINCI_MCBSP_SPCR_XRST : DAVINCI_MCBSP_SPCR_RRST;

	davinci_mcbsp_stop(dev, playback);

	spcr = davinci_mcbsp_read_reg(dev, DAVINCI_MCBSP_SPCR_REG);
	if (spcr & mask) {
		/* start off disabled */
		davinci_mcbsp_write_reg(dev, DAVINCI_MCBSP_SPCR_REG,
					spcr & ~mask);
		toggle_clock(dev, playback);
	}
	if (dev->pcr & (DAVINCI_MCBSP_PCR_FSXM | DAVINCI_MCBSP_PCR_FSRM |
			DAVINCI_MCBSP_PCR_CLKXM | DAVINCI_MCBSP_PCR_CLKRM)) {
		/* Start the sample generator */
		spcr |= DAVINCI_MCBSP_SPCR_GRST;
		davinci_mcbsp_write_reg(dev, DAVINCI_MCBSP_SPCR_REG, spcr);
	}

	if (playback) {
		/* Enable the transmitter */
		spcr = davinci_mcbsp_read_reg(dev, DAVINCI_MCBSP_SPCR_REG);
		spcr |= DAVINCI_MCBSP_SPCR_XRST;
		davinci_mcbsp_write_reg(dev, DAVINCI_MCBSP_SPCR_REG, spcr);

		/* wait for any unexpected frame sync error to occur */
		udelay(100);

		/* Disable the transmitter to clear any outstanding XSYNCERR */
		spcr = davinci_mcbsp_read_reg(dev, DAVINCI_MCBSP_SPCR_REG);
		spcr &= ~DAVINCI_MCBSP_SPCR_XRST;
		davinci_mcbsp_write_reg(dev, DAVINCI_MCBSP_SPCR_REG, spcr);
		toggle_clock(dev, playback);
	}

	return 0;
}