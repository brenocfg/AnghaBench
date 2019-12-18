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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int setup_sample_format (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int setup_sample_rate (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tscs42xx_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params,
		struct snd_soc_dai *codec_dai)
{
	struct snd_soc_component *component = codec_dai->component;
	int ret;

	ret = setup_sample_format(component, params_format(params));
	if (ret < 0) {
		dev_err(component->dev, "Failed to setup sample format (%d)\n",
			ret);
		return ret;
	}

	ret = setup_sample_rate(component, params_rate(params));
	if (ret < 0) {
		dev_err(component->dev,
				"Failed to setup sample rate (%d)\n", ret);
		return ret;
	}

	return 0;
}