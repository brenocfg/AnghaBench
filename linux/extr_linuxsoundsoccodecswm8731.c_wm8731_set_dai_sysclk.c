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
struct wm8731_priv {int sysclk_type; unsigned int sysclk; int /*<<< orphan*/ * constraints; int /*<<< orphan*/  mclk; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  WM8731_SYSCLK_MCLK 129 
#define  WM8731_SYSCLK_XTAL 128 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct wm8731_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  wm8731_constraints_11289600_16934400 ; 
 int /*<<< orphan*/  wm8731_constraints_12000000 ; 
 int /*<<< orphan*/  wm8731_constraints_12288000_18432000 ; 

__attribute__((used)) static int wm8731_set_dai_sysclk(struct snd_soc_dai *codec_dai,
		int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct wm8731_priv *wm8731 = snd_soc_component_get_drvdata(component);

	switch (clk_id) {
	case WM8731_SYSCLK_XTAL:
	case WM8731_SYSCLK_MCLK:
		if (wm8731->mclk && clk_set_rate(wm8731->mclk, freq))
			return -EINVAL;
		wm8731->sysclk_type = clk_id;
		break;
	default:
		return -EINVAL;
	}

	switch (freq) {
	case 0:
		wm8731->constraints = NULL;
		break;
	case 12000000:
		wm8731->constraints = &wm8731_constraints_12000000;
		break;
	case 12288000:
	case 18432000:
		wm8731->constraints = &wm8731_constraints_12288000_18432000;
		break;
	case 16934400:
	case 11289600:
		wm8731->constraints = &wm8731_constraints_11289600_16934400;
		break;
	default:
		return -EINVAL;
	}

	wm8731->sysclk = freq;

	snd_soc_dapm_sync(dapm);

	return 0;
}