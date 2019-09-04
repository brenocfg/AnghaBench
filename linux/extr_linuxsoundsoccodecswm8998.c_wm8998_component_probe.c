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
struct TYPE_2__ {struct arizona* arizona; } ;
struct wm8998_priv {TYPE_1__ core; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct arizona {int /*<<< orphan*/  regmap; struct snd_soc_dapm_context* dapm; } ;

/* Variables and functions */
 int /*<<< orphan*/  arizona_init_gpio (struct snd_soc_component*) ; 
 int arizona_init_spk (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_disable_pin (struct snd_soc_component*,char*) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct wm8998_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_init_regmap (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8998_component_probe(struct snd_soc_component *component)
{
	struct wm8998_priv *priv = snd_soc_component_get_drvdata(component);
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct arizona *arizona = priv->core.arizona;
	int ret;

	arizona->dapm = dapm;
	snd_soc_component_init_regmap(component, arizona->regmap);

	ret = arizona_init_spk(component);
	if (ret < 0)
		return ret;

	arizona_init_gpio(component);

	snd_soc_component_disable_pin(component, "HAPTICS");

	return 0;
}