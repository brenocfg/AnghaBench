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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {TYPE_1__* card; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  constraints_slave ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int snd_pcm_hw_constraint_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i_sabre_codec_dai_startup_slave(
		struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	int ret;

	ret = snd_pcm_hw_constraint_list(substream->runtime,
			0, SNDRV_PCM_HW_PARAM_RATE, &constraints_slave);
	if (ret != 0) {
		dev_err(component->card->dev, "Failed to setup rates constraints: %d\n", ret);
	}

	return ret;
}