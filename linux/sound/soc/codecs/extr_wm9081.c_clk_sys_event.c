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
struct wm9081_priv {int sysclk_source; int /*<<< orphan*/  mclk_rate; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAPM_POST_PMD 131 
#define  SND_SOC_DAPM_PRE_PMU 130 
#define  WM9081_SYSCLK_FLL_MCLK 129 
#define  WM9081_SYSCLK_MCLK 128 
 int /*<<< orphan*/  configure_clock (struct snd_soc_component*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct wm9081_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm9081_set_fll (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_sys_event(struct snd_soc_dapm_widget *w,
			 struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct wm9081_priv *wm9081 = snd_soc_component_get_drvdata(component);

	/* This should be done on init() for bypass paths */
	switch (wm9081->sysclk_source) {
	case WM9081_SYSCLK_MCLK:
		dev_dbg(component->dev, "Using %dHz MCLK\n", wm9081->mclk_rate);
		break;
	case WM9081_SYSCLK_FLL_MCLK:
		dev_dbg(component->dev, "Using %dHz MCLK with FLL\n",
			wm9081->mclk_rate);
		break;
	default:
		dev_err(component->dev, "System clock not configured\n");
		return -EINVAL;
	}

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		configure_clock(component);
		break;

	case SND_SOC_DAPM_POST_PMD:
		/* Disable the FLL if it's running */
		wm9081_set_fll(component, 0, 0, 0);
		break;
	}

	return 0;
}