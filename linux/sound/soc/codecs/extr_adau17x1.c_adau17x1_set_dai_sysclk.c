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
struct snd_soc_dai {int /*<<< orphan*/  component; } ;
struct adau {int clk_src; unsigned int sysclk; int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
#define  ADAU17X1_CLK_SRC_MCLK 130 
#define  ADAU17X1_CLK_SRC_PLL 129 
#define  ADAU17X1_CLK_SRC_PLL_AUTO 128 
 int EINVAL ; 
 int /*<<< orphan*/  adau17x1_dapm_pll_route ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (int /*<<< orphan*/ ) ; 
 struct adau* snd_soc_component_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_del_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int adau17x1_set_dai_sysclk(struct snd_soc_dai *dai,
		int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(dai->component);
	struct adau *adau = snd_soc_component_get_drvdata(dai->component);
	bool is_pll;
	bool was_pll;

	switch (clk_id) {
	case ADAU17X1_CLK_SRC_MCLK:
		is_pll = false;
		break;
	case ADAU17X1_CLK_SRC_PLL_AUTO:
		if (!adau->mclk)
			return -EINVAL;
		/* Fall-through */
	case ADAU17X1_CLK_SRC_PLL:
		is_pll = true;
		break;
	default:
		return -EINVAL;
	}

	switch (adau->clk_src) {
	case ADAU17X1_CLK_SRC_MCLK:
		was_pll = false;
		break;
	case ADAU17X1_CLK_SRC_PLL:
	case ADAU17X1_CLK_SRC_PLL_AUTO:
		was_pll = true;
		break;
	default:
		return -EINVAL;
	}

	adau->sysclk = freq;

	if (is_pll != was_pll) {
		if (is_pll) {
			snd_soc_dapm_add_routes(dapm,
				&adau17x1_dapm_pll_route, 1);
		} else {
			snd_soc_dapm_del_routes(dapm,
				&adau17x1_dapm_pll_route, 1);
		}
	}

	adau->clk_src = clk_id;

	return 0;
}