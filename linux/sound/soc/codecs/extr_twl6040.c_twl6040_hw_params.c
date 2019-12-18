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
struct twl6040_data {int sysclk; int /*<<< orphan*/  pll; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TWL6040_SYSCLK_SEL_HPPLL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 struct twl6040_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static int twl6040_hw_params(struct snd_pcm_substream *substream,
			struct snd_pcm_hw_params *params,
			struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct twl6040_data *priv = snd_soc_component_get_drvdata(component);
	int rate;

	rate = params_rate(params);
	switch (rate) {
	case 11250:
	case 22500:
	case 44100:
	case 88200:
		/* These rates are not supported when HPPLL is in use */
		if (unlikely(priv->pll == TWL6040_SYSCLK_SEL_HPPLL)) {
			dev_err(component->dev, "HPPLL does not support rate %d\n",
				rate);
			return -EINVAL;
		}
		priv->sysclk = 17640000;
		break;
	case 8000:
	case 16000:
	case 32000:
	case 48000:
	case 96000:
		priv->sysclk = 19200000;
		break;
	default:
		dev_err(component->dev, "unsupported rate %d\n", rate);
		return -EINVAL;
	}

	return 0;
}