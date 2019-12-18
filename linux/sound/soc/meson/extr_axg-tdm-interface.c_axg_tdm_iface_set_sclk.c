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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct axg_tdm_iface {unsigned long slots; unsigned long slot_width; unsigned long mclk_rate; int /*<<< orphan*/  fmt; int /*<<< orphan*/  sclk; int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ axg_tdm_sclk_invert (int /*<<< orphan*/ ) ; 
 int clk_set_phase (int /*<<< orphan*/ ,int) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 unsigned long params_rate (struct snd_pcm_hw_params*) ; 
 struct axg_tdm_iface* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int axg_tdm_iface_set_sclk(struct snd_soc_dai *dai,
				  struct snd_pcm_hw_params *params)
{
	struct axg_tdm_iface *iface = snd_soc_dai_get_drvdata(dai);
	unsigned long srate;
	int ret;

	srate = iface->slots * iface->slot_width * params_rate(params);

	if (!iface->mclk_rate) {
		/* If no specific mclk is requested, default to bit clock * 4 */
		clk_set_rate(iface->mclk, 4 * srate);
	} else {
		/* Check if we can actually get the bit clock from mclk */
		if (iface->mclk_rate % srate) {
			dev_err(dai->dev,
				"can't derive sclk %lu from mclk %lu\n",
				srate, iface->mclk_rate);
			return -EINVAL;
		}
	}

	ret = clk_set_rate(iface->sclk, srate);
	if (ret) {
		dev_err(dai->dev, "setting bit clock failed: %d\n", ret);
		return ret;
	}

	/* Set the bit clock inversion */
	ret = clk_set_phase(iface->sclk,
			    axg_tdm_sclk_invert(iface->fmt) ? 0 : 180);
	if (ret) {
		dev_err(dai->dev, "setting bit clock phase failed: %d\n", ret);
		return ret;
	}

	return ret;
}