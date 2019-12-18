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
struct snd_soc_component {int dummy; } ;
struct madera {int /*<<< orphan*/  dapm_ptr_lock; int /*<<< orphan*/  dapm; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/ * adsp; struct madera* madera; } ;
struct cs47l90 {TYPE_1__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS47L90_MONO_OUTPUTS ; 
 int CS47L90_NUM_ADSP ; 
 int /*<<< orphan*/  madera_adsp_rate_controls ; 
 int madera_init_inputs (struct snd_soc_component*) ; 
 int madera_init_outputs (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_component_disable_pin (struct snd_soc_component*,char*) ; 
 int /*<<< orphan*/  snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct cs47l90* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_init_regmap (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm_adsp2_component_probe (int /*<<< orphan*/ *,struct snd_soc_component*) ; 

__attribute__((used)) static int cs47l90_component_probe(struct snd_soc_component *component)
{
	struct cs47l90 *cs47l90 = snd_soc_component_get_drvdata(component);
	struct madera *madera = cs47l90->core.madera;
	int ret, i;

	snd_soc_component_init_regmap(component, madera->regmap);

	mutex_lock(&madera->dapm_ptr_lock);
	madera->dapm = snd_soc_component_get_dapm(component);
	mutex_unlock(&madera->dapm_ptr_lock);

	ret = madera_init_inputs(component);
	if (ret)
		return ret;

	ret = madera_init_outputs(component, CS47L90_MONO_OUTPUTS);
	if (ret)
		return ret;

	snd_soc_component_disable_pin(component, "HAPTICS");

	ret = snd_soc_add_component_controls(component,
					     madera_adsp_rate_controls,
					     CS47L90_NUM_ADSP);
	if (ret)
		return ret;

	for (i = 0; i < CS47L90_NUM_ADSP; i++)
		wm_adsp2_component_probe(&cs47l90->core.adsp[i], component);

	return 0;
}