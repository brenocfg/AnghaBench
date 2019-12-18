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
typedef  int u16 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct aic26 {int mclk; int datfm; scalar_t__ master; TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AIC26_DIV_1 ; 
 int AIC26_DIV_1_5 ; 
 int AIC26_DIV_2 ; 
 int AIC26_DIV_3 ; 
 int AIC26_DIV_4 ; 
 int AIC26_DIV_6 ; 
 int /*<<< orphan*/  AIC26_REG_AUDIO_CTRL1 ; 
 int /*<<< orphan*/  AIC26_REG_AUDIO_CTRL3 ; 
 int /*<<< orphan*/  AIC26_REG_PLL_PROG1 ; 
 int /*<<< orphan*/  AIC26_REG_PLL_PROG2 ; 
 int AIC26_WLEN_16 ; 
 int AIC26_WLEN_24 ; 
 int AIC26_WLEN_32 ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 struct aic26* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aic26_hw_params(struct snd_pcm_substream *substream,
			   struct snd_pcm_hw_params *params,
			   struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct aic26 *aic26 = snd_soc_component_get_drvdata(component);
	int fsref, divisor, wlen, pval, jval, dval, qval;
	u16 reg;

	dev_dbg(&aic26->spi->dev, "aic26_hw_params(substream=%p, params=%p)\n",
		substream, params);
	dev_dbg(&aic26->spi->dev, "rate=%i width=%d\n", params_rate(params),
		params_width(params));

	switch (params_rate(params)) {
	case 8000:  fsref = 48000; divisor = AIC26_DIV_6; break;
	case 11025: fsref = 44100; divisor = AIC26_DIV_4; break;
	case 12000: fsref = 48000; divisor = AIC26_DIV_4; break;
	case 16000: fsref = 48000; divisor = AIC26_DIV_3; break;
	case 22050: fsref = 44100; divisor = AIC26_DIV_2; break;
	case 24000: fsref = 48000; divisor = AIC26_DIV_2; break;
	case 32000: fsref = 48000; divisor = AIC26_DIV_1_5; break;
	case 44100: fsref = 44100; divisor = AIC26_DIV_1; break;
	case 48000: fsref = 48000; divisor = AIC26_DIV_1; break;
	default:
		dev_dbg(&aic26->spi->dev, "bad rate\n"); return -EINVAL;
	}

	/* select data word length */
	switch (params_width(params)) {
	case 8:  wlen = AIC26_WLEN_16; break;
	case 16: wlen = AIC26_WLEN_16; break;
	case 24: wlen = AIC26_WLEN_24; break;
	case 32: wlen = AIC26_WLEN_32; break;
	default:
		dev_dbg(&aic26->spi->dev, "bad format\n"); return -EINVAL;
	}

	/**
	 * Configure PLL
	 * fsref = (mclk * PLLM) / 2048
	 * where PLLM = J.DDDD (DDDD register ranges from 0 to 9999, decimal)
	 */
	pval = 1;
	/* compute J portion of multiplier */
	jval = fsref / (aic26->mclk / 2048);
	/* compute fractional DDDD component of multiplier */
	dval = fsref - (jval * (aic26->mclk / 2048));
	dval = (10000 * dval) / (aic26->mclk / 2048);
	dev_dbg(&aic26->spi->dev, "Setting PLLM to %d.%04d\n", jval, dval);
	qval = 0;
	reg = 0x8000 | qval << 11 | pval << 8 | jval << 2;
	snd_soc_component_write(component, AIC26_REG_PLL_PROG1, reg);
	reg = dval << 2;
	snd_soc_component_write(component, AIC26_REG_PLL_PROG2, reg);

	/* Audio Control 3 (master mode, fsref rate) */
	if (aic26->master)
		reg = 0x0800;
	if (fsref == 48000)
		reg = 0x2000;
	snd_soc_component_update_bits(component, AIC26_REG_AUDIO_CTRL3, 0xf800, reg);

	/* Audio Control 1 (FSref divisor) */
	reg = wlen | aic26->datfm | (divisor << 3) | divisor;
	snd_soc_component_update_bits(component, AIC26_REG_AUDIO_CTRL1, 0xfff, reg);

	return 0;
}