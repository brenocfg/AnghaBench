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
struct adau1701 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU1701_DSPCTRL ; 
 unsigned int ADAU1701_DSPCTRL_DAM ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct adau1701* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int adau1701_digital_mute(struct snd_soc_dai *dai, int mute)
{
	struct snd_soc_component *component = dai->component;
	unsigned int mask = ADAU1701_DSPCTRL_DAM;
	struct adau1701 *adau1701 = snd_soc_component_get_drvdata(component);
	unsigned int val;

	if (mute)
		val = 0;
	else
		val = mask;

	regmap_update_bits(adau1701->regmap, ADAU1701_DSPCTRL, mask, val);

	return 0;
}