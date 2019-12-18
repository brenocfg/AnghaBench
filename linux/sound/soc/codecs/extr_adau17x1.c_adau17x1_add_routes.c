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
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct adau {scalar_t__ clk_src; } ;

/* Variables and functions */
 scalar_t__ ADAU17X1_CLK_SRC_MCLK ; 
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adau17x1_dapm_pll_route ; 
 int /*<<< orphan*/ * adau17x1_dapm_routes ; 
 int /*<<< orphan*/ * adau17x1_dsp_dapm_routes ; 
 scalar_t__ adau17x1_has_dsp (struct adau*) ; 
 int /*<<< orphan*/ * adau17x1_no_dsp_dapm_routes ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct adau* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ *,int) ; 

int adau17x1_add_routes(struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct adau *adau = snd_soc_component_get_drvdata(component);
	int ret;

	ret = snd_soc_dapm_add_routes(dapm, adau17x1_dapm_routes,
		ARRAY_SIZE(adau17x1_dapm_routes));
	if (ret)
		return ret;

	if (adau17x1_has_dsp(adau)) {
		ret = snd_soc_dapm_add_routes(dapm, adau17x1_dsp_dapm_routes,
			ARRAY_SIZE(adau17x1_dsp_dapm_routes));
	} else {
		ret = snd_soc_dapm_add_routes(dapm, adau17x1_no_dsp_dapm_routes,
			ARRAY_SIZE(adau17x1_no_dsp_dapm_routes));
	}

	if (adau->clk_src != ADAU17X1_CLK_SRC_MCLK)
		snd_soc_dapm_add_routes(dapm, &adau17x1_dapm_pll_route, 1);

	return ret;
}