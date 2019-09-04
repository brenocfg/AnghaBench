#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_hw_params {int dummy; } ;
struct uniphier_aio_sub {int setting; int /*<<< orphan*/  vol; struct snd_pcm_hw_params params; } ;
struct uniphier_aio {TYPE_2__* chip; struct uniphier_aio_sub* sub; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {size_t stream; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_CLK_A ; 
 int EINVAL ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_OUT ; 
 int /*<<< orphan*/  aio_port_reset (struct uniphier_aio_sub*) ; 
 int /*<<< orphan*/  aio_port_set_volume (struct uniphier_aio_sub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_src_reset (struct uniphier_aio_sub*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct uniphier_aio* uniphier_priv (struct snd_soc_dai*) ; 

__attribute__((used)) static int uniphier_aio_hw_params(struct snd_pcm_substream *substream,
				  struct snd_pcm_hw_params *params,
				  struct snd_soc_dai *dai)
{
	struct uniphier_aio *aio = uniphier_priv(dai);
	struct uniphier_aio_sub *sub = &aio->sub[substream->stream];
	struct device *dev = &aio->chip->pdev->dev;
	int freq, ret;

	switch (params_rate(params)) {
	case 48000:
	case 32000:
	case 24000:
		freq = 12288000;
		break;
	case 44100:
	case 22050:
		freq = 11289600;
		break;
	default:
		dev_err(dev, "Rate is not supported(%d)\n",
			params_rate(params));
		return -EINVAL;
	}
	ret = snd_soc_dai_set_sysclk(dai, AUD_CLK_A,
				     freq, SND_SOC_CLOCK_OUT);
	if (ret)
		return ret;

	sub->params = *params;
	sub->setting = 1;

	aio_port_reset(sub);
	aio_port_set_volume(sub, sub->vol);
	aio_src_reset(sub);

	return 0;
}