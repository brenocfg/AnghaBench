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
struct arizona_priv {struct arizona* arizona; } ;
struct arizona {int type; } ;

/* Variables and functions */
#define  CS47L24 130 
#define  WM1831 129 
#define  WM8997 128 
 int /*<<< orphan*/  arizona_spkl ; 
 int /*<<< orphan*/  arizona_spkr ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct arizona_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ *,int) ; 

int arizona_init_spk(struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct arizona_priv *priv = snd_soc_component_get_drvdata(component);
	struct arizona *arizona = priv->arizona;
	int ret;

	ret = snd_soc_dapm_new_controls(dapm, &arizona_spkl, 1);
	if (ret != 0)
		return ret;

	switch (arizona->type) {
	case WM8997:
	case CS47L24:
	case WM1831:
		break;
	default:
		ret = snd_soc_dapm_new_controls(dapm, &arizona_spkr, 1);
		if (ret != 0)
			return ret;
		break;
	}

	return 0;
}