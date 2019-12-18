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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct max98088_priv {int /*<<< orphan*/ * eq_texts; int /*<<< orphan*/  eq_textcnt; struct max98088_cdata* dai; struct max98088_pdata* pdata; } ;
struct max98088_pdata {int eq_cfgcnt; struct max98088_eq_cfg* eq_cfg; } ;
struct max98088_eq_cfg {int /*<<< orphan*/  band5; int /*<<< orphan*/  band4; int /*<<< orphan*/  band3; int /*<<< orphan*/  band2; int /*<<< orphan*/  band1; scalar_t__ rate; int /*<<< orphan*/  name; } ;
struct max98088_cdata {int rate; int eq_sel; } ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  M98088_EQ2EN ; 
 int /*<<< orphan*/  M98088_REG_49_CFG_LEVEL ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  m98088_eq_band (struct snd_soc_component*,int,int,int /*<<< orphan*/ ) ; 
 struct max98088_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max98088_setup_eq2(struct snd_soc_component *component)
{
       struct max98088_priv *max98088 = snd_soc_component_get_drvdata(component);
       struct max98088_pdata *pdata = max98088->pdata;
       struct max98088_eq_cfg *coef_set;
       int best, best_val, save, i, sel, fs;
       struct max98088_cdata *cdata;

       cdata = &max98088->dai[1];

       if (!pdata || !max98088->eq_textcnt)
               return;

       /* Find the selected configuration with nearest sample rate */
       fs = cdata->rate;

       sel = cdata->eq_sel;
       best = 0;
       best_val = INT_MAX;
       for (i = 0; i < pdata->eq_cfgcnt; i++) {
               if (strcmp(pdata->eq_cfg[i].name, max98088->eq_texts[sel]) == 0 &&
                   abs(pdata->eq_cfg[i].rate - fs) < best_val) {
                       best = i;
                       best_val = abs(pdata->eq_cfg[i].rate - fs);
               }
       }

       dev_dbg(component->dev, "Selected %s/%dHz for %dHz sample rate\n",
               pdata->eq_cfg[best].name,
               pdata->eq_cfg[best].rate, fs);

       /* Disable EQ while configuring, and save current on/off state */
       save = snd_soc_component_read32(component, M98088_REG_49_CFG_LEVEL);
       snd_soc_component_update_bits(component, M98088_REG_49_CFG_LEVEL, M98088_EQ2EN, 0);

       coef_set = &pdata->eq_cfg[sel];

       m98088_eq_band(component, 1, 0, coef_set->band1);
       m98088_eq_band(component, 1, 1, coef_set->band2);
       m98088_eq_band(component, 1, 2, coef_set->band3);
       m98088_eq_band(component, 1, 3, coef_set->band4);
       m98088_eq_band(component, 1, 4, coef_set->band5);

       /* Restore the original on/off state */
       snd_soc_component_update_bits(component, M98088_REG_49_CFG_LEVEL, M98088_EQ2EN,
               save);
}