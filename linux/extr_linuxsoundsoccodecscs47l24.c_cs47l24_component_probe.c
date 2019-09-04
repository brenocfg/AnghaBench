#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * adsp; struct arizona* arizona; } ;
struct cs47l24_priv {TYPE_1__ core; } ;
struct arizona {int /*<<< orphan*/  regmap; struct snd_soc_dapm_context* dapm; } ;

/* Variables and functions */
 int /*<<< orphan*/ * arizona_adsp2_rate_controls ; 
 int /*<<< orphan*/  arizona_init_gpio (struct snd_soc_component*) ; 
 int /*<<< orphan*/  arizona_init_mono (struct snd_soc_component*) ; 
 int arizona_init_spk (struct snd_soc_component*) ; 
 int snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snd_soc_component_disable_pin (struct snd_soc_component*,char*) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct cs47l24_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_init_regmap (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int wm_adsp2_component_probe (int /*<<< orphan*/ *,struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm_adsp2_component_remove (int /*<<< orphan*/ *,struct snd_soc_component*) ; 

__attribute__((used)) static int cs47l24_component_probe(struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct cs47l24_priv *priv = snd_soc_component_get_drvdata(component);
	struct arizona *arizona = priv->core.arizona;
	int ret;

	arizona->dapm = dapm;
	snd_soc_component_init_regmap(component, arizona->regmap);

	ret = arizona_init_spk(component);
	if (ret < 0)
		return ret;

	arizona_init_gpio(component);
	arizona_init_mono(component);

	ret = wm_adsp2_component_probe(&priv->core.adsp[1], component);
	if (ret)
		goto err_adsp2_codec_probe;

	ret = wm_adsp2_component_probe(&priv->core.adsp[2], component);
	if (ret)
		goto err_adsp2_codec_probe;

	ret = snd_soc_add_component_controls(component,
					     &arizona_adsp2_rate_controls[1],
					     2);
	if (ret)
		goto err_adsp2_codec_probe;

	snd_soc_component_disable_pin(component, "HAPTICS");

	return 0;

err_adsp2_codec_probe:
	wm_adsp2_component_remove(&priv->core.adsp[1], component);
	wm_adsp2_component_remove(&priv->core.adsp[2], component);

	return ret;
}