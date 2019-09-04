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
typedef  int u32 ;
struct ssp_priv {int dai_fmt; int sysclk; struct ssp_device* ssp; } ;
struct ssp_device {TYPE_1__* pdev; int /*<<< orphan*/  type; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_dmaengine_dai_dma_data {int dummy; } ;
struct pxa_ssp_clock_mode {int rate; int acds; int scdb; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PXA3xx_SSP ; 
#define  SNDRV_PCM_FORMAT_S16_LE 131 
#define  SNDRV_PCM_FORMAT_S24_LE 130 
#define  SNDRV_PCM_FORMAT_S32_LE 129 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 128 
 int /*<<< orphan*/  SSACD ; 
 int SSACD_ACDS (int) ; 
 int SSACD_SCDB_1X ; 
 int /*<<< orphan*/  SSCR0 ; 
 int SSCR0_ACS ; 
 int SSCR0_DSS ; 
 int SSCR0_DataSize (int) ; 
 int SSCR0_ECS ; 
 int SSCR0_EDSS ; 
 int SSCR0_FPCKE ; 
 int SSCR0_MOD ; 
 int SSCR0_SSE ; 
 int /*<<< orphan*/  SSPSP ; 
 int SSPSP_DMYSTOP (int) ; 
 int SSPSP_DMYSTRT (int) ; 
 int SSPSP_EDMYSTOP (int) ; 
 int SSPSP_SFRMDLY (int) ; 
 int SSPSP_SFRMWDTH (int) ; 
 int /*<<< orphan*/  SSTSA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dump_registers (struct ssp_device*) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 struct pxa_ssp_clock_mode* pxa_ssp_clock_modes ; 
 int pxa_ssp_configure_dai_fmt (struct ssp_priv*) ; 
 int pxa_ssp_read_reg (struct ssp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa_ssp_set_dma_params (struct ssp_device*,int,int,struct snd_dmaengine_dai_dma_data*) ; 
 int pxa_ssp_set_pll (struct ssp_priv*,int) ; 
 int /*<<< orphan*/  pxa_ssp_set_scr (struct ssp_device*,int) ; 
 int /*<<< orphan*/  pxa_ssp_write_reg (struct ssp_device*,int /*<<< orphan*/ ,int) ; 
 int snd_pcm_format_physical_width (int) ; 
 struct snd_dmaengine_dai_dma_data* snd_soc_dai_get_dma_data (struct snd_soc_dai*,struct snd_pcm_substream*) ; 
 struct ssp_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int pxa_ssp_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *cpu_dai)
{
	struct ssp_priv *priv = snd_soc_dai_get_drvdata(cpu_dai);
	struct ssp_device *ssp = priv->ssp;
	int chn = params_channels(params);
	u32 sscr0, sspsp;
	int width = snd_pcm_format_physical_width(params_format(params));
	int ttsa = pxa_ssp_read_reg(ssp, SSTSA) & 0xf;
	struct snd_dmaengine_dai_dma_data *dma_data;
	int rate = params_rate(params);
	int bclk = rate * chn * (width / 8);
	int ret;

	dma_data = snd_soc_dai_get_dma_data(cpu_dai, substream);

	/* Network mode with one active slot (ttsa == 1) can be used
	 * to force 16-bit frame width on the wire (for S16_LE), even
	 * with two channels. Use 16-bit DMA transfers for this case.
	 */
	pxa_ssp_set_dma_params(ssp,
		((chn == 2) && (ttsa != 1)) || (width == 32),
		substream->stream == SNDRV_PCM_STREAM_PLAYBACK, dma_data);

	/* we can only change the settings if the port is not in use */
	if (pxa_ssp_read_reg(ssp, SSCR0) & SSCR0_SSE)
		return 0;

	ret = pxa_ssp_configure_dai_fmt(priv);
	if (ret < 0)
		return ret;

	/* clear selected SSP bits */
	sscr0 = pxa_ssp_read_reg(ssp, SSCR0) & ~(SSCR0_DSS | SSCR0_EDSS);

	/* bit size */
	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		if (ssp->type == PXA3xx_SSP)
			sscr0 |= SSCR0_FPCKE;
		sscr0 |= SSCR0_DataSize(16);
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		sscr0 |= (SSCR0_EDSS | SSCR0_DataSize(8));
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		sscr0 |= (SSCR0_EDSS | SSCR0_DataSize(16));
		break;
	}
	pxa_ssp_write_reg(ssp, SSCR0, sscr0);

	if (sscr0 & SSCR0_ACS) {
		ret = pxa_ssp_set_pll(priv, bclk);

		/*
		 * If we were able to generate the bclk directly,
		 * all is fine. Otherwise, look up the closest rate
		 * from the table and also set the dividers.
		 */

		if (ret < 0) {
			const struct pxa_ssp_clock_mode *m;
			int ssacd, acds;

			for (m = pxa_ssp_clock_modes; m->rate; m++) {
				if (m->rate == rate)
					break;
			}

			if (!m->rate)
				return -EINVAL;

			acds = m->acds;

			/* The values in the table are for 16 bits */
			if (width == 32)
				acds--;

			ret = pxa_ssp_set_pll(priv, bclk);
			if (ret < 0)
				return ret;

			ssacd = pxa_ssp_read_reg(ssp, SSACD);
			ssacd &= ~(SSACD_ACDS(7) | SSACD_SCDB_1X);
			ssacd |= SSACD_ACDS(m->acds);
			ssacd |= m->scdb;
			pxa_ssp_write_reg(ssp, SSACD, ssacd);
		}
	} else if (sscr0 & SSCR0_ECS) {
		/*
		 * For setups with external clocking, the PLL and its diviers
		 * are not active. Instead, the SCR bits in SSCR0 can be used
		 * to divide the clock.
		 */
		pxa_ssp_set_scr(ssp, bclk / rate);
	}

	switch (priv->dai_fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
	       sspsp = pxa_ssp_read_reg(ssp, SSPSP);

		if (((priv->sysclk / bclk) == 64) && (width == 16)) {
			/* This is a special case where the bitclk is 64fs
			 * and we're not dealing with 2*32 bits of audio
			 * samples.
			 *
			 * The SSP values used for that are all found out by
			 * trying and failing a lot; some of the registers
			 * needed for that mode are only available on PXA3xx.
			 */
			if (ssp->type != PXA3xx_SSP)
				return -EINVAL;

			sspsp |= SSPSP_SFRMWDTH(width * 2);
			sspsp |= SSPSP_SFRMDLY(width * 4);
			sspsp |= SSPSP_EDMYSTOP(3);
			sspsp |= SSPSP_DMYSTOP(3);
			sspsp |= SSPSP_DMYSTRT(1);
		} else {
			/* The frame width is the width the LRCLK is
			 * asserted for; the delay is expressed in
			 * half cycle units.  We need the extra cycle
			 * because the data starts clocking out one BCLK
			 * after LRCLK changes polarity.
			 */
			sspsp |= SSPSP_SFRMWDTH(width + 1);
			sspsp |= SSPSP_SFRMDLY((width + 1) * 2);
			sspsp |= SSPSP_DMYSTRT(1);
		}

		pxa_ssp_write_reg(ssp, SSPSP, sspsp);
		break;
	default:
		break;
	}

	/* When we use a network mode, we always require TDM slots
	 * - complain loudly and fail if they've not been set up yet.
	 */
	if ((sscr0 & SSCR0_MOD) && !ttsa) {
		dev_err(&ssp->pdev->dev, "No TDM timeslot configured\n");
		return -EINVAL;
	}

	dump_registers(ssp);

	return 0;
}