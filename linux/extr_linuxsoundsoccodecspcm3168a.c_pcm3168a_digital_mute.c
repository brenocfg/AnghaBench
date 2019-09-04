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
struct snd_soc_component {int dummy; } ;
struct pcm3168a_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCM3168A_DAC_MUTE ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct pcm3168a_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int pcm3168a_digital_mute(struct snd_soc_dai *dai, int mute)
{
	struct snd_soc_component *component = dai->component;
	struct pcm3168a_priv *pcm3168a = snd_soc_component_get_drvdata(component);

	regmap_write(pcm3168a->regmap, PCM3168A_DAC_MUTE, mute ? 0xff : 0);

	return 0;
}