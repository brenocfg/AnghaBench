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
struct wm_adsp {scalar_t__ base; int /*<<< orphan*/  regmap; } ;
struct snd_soc_dapm_widget {size_t shift; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADSP2_CLK_SEL_MASK ; 
 unsigned int ADSP2_CLK_SEL_SHIFT ; 
 scalar_t__ ADSP2_CLOCKING ; 
 int /*<<< orphan*/  adsp_err (struct wm_adsp*,char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 struct wm_adsp* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

int wm_adsp2_set_dspclk(struct snd_soc_dapm_widget *w, unsigned int freq)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct wm_adsp *dsps = snd_soc_component_get_drvdata(component);
	struct wm_adsp *dsp = &dsps[w->shift];
	int ret;

	ret = regmap_update_bits(dsp->regmap, dsp->base + ADSP2_CLOCKING,
				 ADSP2_CLK_SEL_MASK,
				 freq << ADSP2_CLK_SEL_SHIFT);
	if (ret)
		adsp_err(dsp, "Failed to set clock rate: %d\n", ret);

	return ret;
}