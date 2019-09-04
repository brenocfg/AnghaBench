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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct snd_kcontrol {TYPE_1__ id; } ;
struct TYPE_5__ {unsigned int* item; } ;
struct TYPE_6__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct max98095_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/ * eq_texts; struct max98095_cdata* dai; int /*<<< orphan*/  eq_textcnt; struct max98095_pdata* pdata; } ;
struct max98095_pdata {unsigned int eq_cfgcnt; struct max98095_eq_cfg* eq_cfg; } ;
struct max98095_eq_cfg {int /*<<< orphan*/  band5; int /*<<< orphan*/  band4; int /*<<< orphan*/  band3; int /*<<< orphan*/  band2; int /*<<< orphan*/  band1; scalar_t__ rate; int /*<<< orphan*/  name; } ;
struct max98095_cdata {unsigned int eq_sel; int rate; } ;

/* Variables and functions */
 int EINVAL ; 
 int INT_MAX ; 
 int /*<<< orphan*/  M98095_00F_HOST_CFG ; 
 int /*<<< orphan*/  M98095_088_CFG_LEVEL ; 
 int M98095_EQ1EN ; 
 int M98095_EQ2EN ; 
 int M98095_SEG ; 
 scalar_t__ WARN_ON (int) ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  m98095_eq_band (struct snd_soc_component*,int,int,int /*<<< orphan*/ ) ; 
 int max98095_get_eq_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct max98095_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max98095_put_eq_enum(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	struct max98095_pdata *pdata = max98095->pdata;
	int channel = max98095_get_eq_channel(kcontrol->id.name);
	struct max98095_cdata *cdata;
	unsigned int sel = ucontrol->value.enumerated.item[0];
	struct max98095_eq_cfg *coef_set;
	int fs, best, best_val, i;
	int regmask, regsave;

	if (WARN_ON(channel > 1))
		return -EINVAL;

	if (!pdata || !max98095->eq_textcnt)
		return 0;

	if (sel >= pdata->eq_cfgcnt)
		return -EINVAL;

	cdata = &max98095->dai[channel];
	cdata->eq_sel = sel;
	fs = cdata->rate;

	/* Find the selected configuration with nearest sample rate */
	best = 0;
	best_val = INT_MAX;
	for (i = 0; i < pdata->eq_cfgcnt; i++) {
		if (strcmp(pdata->eq_cfg[i].name, max98095->eq_texts[sel]) == 0 &&
			abs(pdata->eq_cfg[i].rate - fs) < best_val) {
			best = i;
			best_val = abs(pdata->eq_cfg[i].rate - fs);
		}
	}

	dev_dbg(component->dev, "Selected %s/%dHz for %dHz sample rate\n",
		pdata->eq_cfg[best].name,
		pdata->eq_cfg[best].rate, fs);

	coef_set = &pdata->eq_cfg[best];

	regmask = (channel == 0) ? M98095_EQ1EN : M98095_EQ2EN;

	/* Disable filter while configuring, and save current on/off state */
	regsave = snd_soc_component_read32(component, M98095_088_CFG_LEVEL);
	snd_soc_component_update_bits(component, M98095_088_CFG_LEVEL, regmask, 0);

	mutex_lock(&max98095->lock);
	snd_soc_component_update_bits(component, M98095_00F_HOST_CFG, M98095_SEG, M98095_SEG);
	m98095_eq_band(component, channel, 0, coef_set->band1);
	m98095_eq_band(component, channel, 1, coef_set->band2);
	m98095_eq_band(component, channel, 2, coef_set->band3);
	m98095_eq_band(component, channel, 3, coef_set->band4);
	m98095_eq_band(component, channel, 4, coef_set->band5);
	snd_soc_component_update_bits(component, M98095_00F_HOST_CFG, M98095_SEG, 0);
	mutex_unlock(&max98095->lock);

	/* Restore the original on/off state */
	snd_soc_component_update_bits(component, M98095_088_CFG_LEVEL, regmask, regsave);
	return 0;
}