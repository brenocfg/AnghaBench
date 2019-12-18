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
struct snd_soc_component {int dummy; } ;
struct cs4271_private {int /*<<< orphan*/  regmap; scalar_t__ rate; scalar_t__ deemph; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  CS4271_DACCTL ; 
 int CS4271_DACCTL_DEM_DIS ; 
 int /*<<< orphan*/  CS4271_DACCTL_DEM_MASK ; 
 scalar_t__ abs (scalar_t__) ; 
 scalar_t__* cs4271_deemph ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cs4271_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs4271_set_deemph(struct snd_soc_component *component)
{
	struct cs4271_private *cs4271 = snd_soc_component_get_drvdata(component);
	int i, ret;
	int val = CS4271_DACCTL_DEM_DIS;

	if (cs4271->deemph) {
		/* Find closest de-emphasis freq */
		val = 1;
		for (i = 2; i < ARRAY_SIZE(cs4271_deemph); i++)
			if (abs(cs4271_deemph[i] - cs4271->rate) <
			    abs(cs4271_deemph[val] - cs4271->rate))
				val = i;
		val <<= 4;
	}

	ret = regmap_update_bits(cs4271->regmap, CS4271_DACCTL,
		CS4271_DACCTL_DEM_MASK, val);
	if (ret < 0)
		return ret;
	return 0;
}