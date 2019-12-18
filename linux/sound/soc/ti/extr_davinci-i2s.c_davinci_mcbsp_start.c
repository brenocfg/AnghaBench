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
typedef  int /*<<< orphan*/  u32 ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct davinci_mcbsp_dev {int pcr; } ;

/* Variables and functions */
 int DAVINCI_MCBSP_PCR_FSRM ; 
 int DAVINCI_MCBSP_PCR_FSXM ; 
 int /*<<< orphan*/  DAVINCI_MCBSP_SPCR_FRST ; 
 int /*<<< orphan*/  DAVINCI_MCBSP_SPCR_REG ; 
 int /*<<< orphan*/  DAVINCI_MCBSP_SPCR_RRST ; 
 int /*<<< orphan*/  DAVINCI_MCBSP_SPCR_XRST ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  davinci_mcbsp_read_reg (struct davinci_mcbsp_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  davinci_mcbsp_write_reg (struct davinci_mcbsp_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void davinci_mcbsp_start(struct davinci_mcbsp_dev *dev,
		struct snd_pcm_substream *substream)
{
	int playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	u32 spcr;
	u32 mask = playback ? DAVINCI_MCBSP_SPCR_XRST : DAVINCI_MCBSP_SPCR_RRST;

	/* Enable transmitter or receiver */
	spcr = davinci_mcbsp_read_reg(dev, DAVINCI_MCBSP_SPCR_REG);
	spcr |= mask;

	if (dev->pcr & (DAVINCI_MCBSP_PCR_FSXM | DAVINCI_MCBSP_PCR_FSRM)) {
		/* Start frame sync */
		spcr |= DAVINCI_MCBSP_SPCR_FRST;
	}
	davinci_mcbsp_write_reg(dev, DAVINCI_MCBSP_SPCR_REG, spcr);
}