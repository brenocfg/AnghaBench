#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct soc_mixer_control {int shift; int rshift; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {TYPE_1__* dev; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_5__ {int /*<<< orphan*/ * value; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct arizona {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_DRE_ENABLE ; 
 int /*<<< orphan*/  ARIZONA_OUTPUT_ENABLES_1 ; 
 int EBUSY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct arizona* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_lock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_unlock (struct snd_soc_dapm_context*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  wm5110_clear_pga_volume (struct arizona*,int) ; 

__attribute__((used)) static int wm5110_put_dre(struct snd_kcontrol *kcontrol,
			  struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct arizona *arizona = dev_get_drvdata(component->dev->parent);
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;
	unsigned int ena, dre;
	unsigned int mask = (0x1 << mc->shift) | (0x1 << mc->rshift);
	unsigned int lnew = (!!ucontrol->value.integer.value[0]) << mc->shift;
	unsigned int rnew = (!!ucontrol->value.integer.value[1]) << mc->rshift;
	unsigned int lold, rold;
	unsigned int lena, rena;
	int ret;

	snd_soc_dapm_mutex_lock(dapm);

	ret = regmap_read(arizona->regmap, ARIZONA_OUTPUT_ENABLES_1, &ena);
	if (ret) {
		dev_err(arizona->dev, "Failed to read output state: %d\n", ret);
		goto err;
	}
	ret = regmap_read(arizona->regmap, ARIZONA_DRE_ENABLE, &dre);
	if (ret) {
		dev_err(arizona->dev, "Failed to read DRE state: %d\n", ret);
		goto err;
	}

	lold = dre & (1 << mc->shift);
	rold = dre & (1 << mc->rshift);
	/* Enables are channel wise swapped from the DRE enables */
	lena = ena & (1 << mc->rshift);
	rena = ena & (1 << mc->shift);

	if ((lena && lnew != lold) || (rena && rnew != rold)) {
		dev_err(arizona->dev, "Can't change DRE on active outputs\n");
		ret = -EBUSY;
		goto err;
	}

	ret = regmap_update_bits(arizona->regmap, ARIZONA_DRE_ENABLE,
				 mask, lnew | rnew);
	if (ret) {
		dev_err(arizona->dev, "Failed to set DRE: %d\n", ret);
		goto err;
	}

	/* Force reset of PGA volumes, if turning DRE off */
	if (!lnew && lold)
		wm5110_clear_pga_volume(arizona, mc->shift);

	if (!rnew && rold)
		wm5110_clear_pga_volume(arizona, mc->rshift);

err:
	snd_soc_dapm_mutex_unlock(dapm);

	return ret;
}