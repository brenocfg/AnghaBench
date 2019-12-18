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
struct rt5677_priv {int is_dsp_mode; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int RT5677_PWR_DSP ; 
 int /*<<< orphan*/  RT5677_PWR_DSP1 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct rt5677_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void rt5677_set_dsp_mode(struct snd_soc_component *component, bool on)
{
	struct rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);

	if (on) {
		regmap_update_bits(rt5677->regmap, RT5677_PWR_DSP1,
			RT5677_PWR_DSP, RT5677_PWR_DSP);
		rt5677->is_dsp_mode = true;
	} else {
		regmap_update_bits(rt5677->regmap, RT5677_PWR_DSP1,
			RT5677_PWR_DSP, 0x0);
		rt5677->is_dsp_mode = false;
	}
}