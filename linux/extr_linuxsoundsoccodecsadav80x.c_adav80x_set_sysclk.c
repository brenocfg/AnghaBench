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
struct adav80x {unsigned int sysclk; int clk_src; int* sysclk_pd; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
#define  ADAV80X_CLK_MCLKI 135 
#define  ADAV80X_CLK_PLL1 134 
#define  ADAV80X_CLK_PLL2 133 
#define  ADAV80X_CLK_SYSCLK1 132 
#define  ADAV80X_CLK_SYSCLK2 131 
#define  ADAV80X_CLK_SYSCLK3 130 
#define  ADAV80X_CLK_XIN 129 
#define  ADAV80X_CLK_XTAL 128 
 int /*<<< orphan*/  ADAV80X_ICLK_CTRL1 ; 
 unsigned int ADAV80X_ICLK_CTRL1_ADC_SRC (int) ; 
 unsigned int ADAV80X_ICLK_CTRL1_DAC_SRC (int) ; 
 unsigned int ADAV80X_ICLK_CTRL1_ICLK2_SRC (int) ; 
 int /*<<< orphan*/  ADAV80X_ICLK_CTRL2 ; 
 unsigned int ADAV80X_ICLK_CTRL2_ICLK1_SRC (int) ; 
 int /*<<< orphan*/  ADAV80X_PLL_OUTE ; 
 unsigned int ADAV80X_PLL_OUTE_SYSCLKPD (int) ; 
 int EINVAL ; 
 int SND_SOC_CLOCK_IN ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct adav80x* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin_unlocked (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_force_enable_pin_unlocked (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_lock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_unlock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync_unlocked (struct snd_soc_dapm_context*) ; 

__attribute__((used)) static int adav80x_set_sysclk(struct snd_soc_component *component,
			      int clk_id, int source,
			      unsigned int freq, int dir)
{
	struct adav80x *adav80x = snd_soc_component_get_drvdata(component);
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	if (dir == SND_SOC_CLOCK_IN) {
		switch (clk_id) {
		case ADAV80X_CLK_XIN:
		case ADAV80X_CLK_XTAL:
		case ADAV80X_CLK_MCLKI:
		case ADAV80X_CLK_PLL1:
		case ADAV80X_CLK_PLL2:
			break;
		default:
			return -EINVAL;
		}

		adav80x->sysclk = freq;

		if (adav80x->clk_src != clk_id) {
			unsigned int iclk_ctrl1, iclk_ctrl2;

			adav80x->clk_src = clk_id;
			if (clk_id == ADAV80X_CLK_XTAL)
				clk_id = ADAV80X_CLK_XIN;

			iclk_ctrl1 = ADAV80X_ICLK_CTRL1_DAC_SRC(clk_id) |
					ADAV80X_ICLK_CTRL1_ADC_SRC(clk_id) |
					ADAV80X_ICLK_CTRL1_ICLK2_SRC(clk_id);
			iclk_ctrl2 = ADAV80X_ICLK_CTRL2_ICLK1_SRC(clk_id);

			regmap_write(adav80x->regmap, ADAV80X_ICLK_CTRL1,
				iclk_ctrl1);
			regmap_write(adav80x->regmap, ADAV80X_ICLK_CTRL2,
				iclk_ctrl2);

			snd_soc_dapm_sync(dapm);
		}
	} else {
		unsigned int mask;

		switch (clk_id) {
		case ADAV80X_CLK_SYSCLK1:
		case ADAV80X_CLK_SYSCLK2:
		case ADAV80X_CLK_SYSCLK3:
			break;
		default:
			return -EINVAL;
		}

		clk_id -= ADAV80X_CLK_SYSCLK1;
		mask = ADAV80X_PLL_OUTE_SYSCLKPD(clk_id);

		if (freq == 0) {
			regmap_update_bits(adav80x->regmap, ADAV80X_PLL_OUTE,
				mask, mask);
			adav80x->sysclk_pd[clk_id] = true;
		} else {
			regmap_update_bits(adav80x->regmap, ADAV80X_PLL_OUTE,
				mask, 0);
			adav80x->sysclk_pd[clk_id] = false;
		}

		snd_soc_dapm_mutex_lock(dapm);

		if (adav80x->sysclk_pd[0])
			snd_soc_dapm_disable_pin_unlocked(dapm, "PLL1");
		else
			snd_soc_dapm_force_enable_pin_unlocked(dapm, "PLL1");

		if (adav80x->sysclk_pd[1] || adav80x->sysclk_pd[2])
			snd_soc_dapm_disable_pin_unlocked(dapm, "PLL2");
		else
			snd_soc_dapm_force_enable_pin_unlocked(dapm, "PLL2");

		snd_soc_dapm_sync_unlocked(dapm);

		snd_soc_dapm_mutex_unlock(dapm);
	}

	return 0;
}