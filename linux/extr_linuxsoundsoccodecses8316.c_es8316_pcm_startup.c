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
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct es8316_priv {scalar_t__ sysclk; int /*<<< orphan*/  sysclk_constraints; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct es8316_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int es8316_pcm_startup(struct snd_pcm_substream *substream,
			      struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct es8316_priv *es8316 = snd_soc_component_get_drvdata(component);

	if (es8316->sysclk == 0) {
		dev_err(component->dev, "No sysclk provided\n");
		return -EINVAL;
	}

	/* The set of sample rates that can be supported depends on the
	 * MCLK supplied to the CODEC.
	 */
	snd_pcm_hw_constraint_list(substream->runtime, 0,
				   SNDRV_PCM_HW_PARAM_RATE,
				   &es8316->sysclk_constraints);

	return 0;
}