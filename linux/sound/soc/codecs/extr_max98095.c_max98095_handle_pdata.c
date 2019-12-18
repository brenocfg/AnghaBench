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
typedef  int /*<<< orphan*/  u8 ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct max98095_priv {struct max98095_pdata* pdata; } ;
struct max98095_pdata {scalar_t__ bq_cfgcnt; scalar_t__ eq_cfgcnt; scalar_t__ digmic_right_mode; scalar_t__ digmic_left_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  M98095_087_CFG_MIC ; 
 int /*<<< orphan*/  M98095_DIGMIC_L ; 
 int /*<<< orphan*/  M98095_DIGMIC_R ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  max98095_handle_bq_pdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  max98095_handle_eq_pdata (struct snd_soc_component*) ; 
 struct max98095_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max98095_handle_pdata(struct snd_soc_component *component)
{
	struct max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	struct max98095_pdata *pdata = max98095->pdata;
	u8 regval = 0;

	if (!pdata) {
		dev_dbg(component->dev, "No platform data\n");
		return;
	}

	/* Configure mic for analog/digital mic mode */
	if (pdata->digmic_left_mode)
		regval |= M98095_DIGMIC_L;

	if (pdata->digmic_right_mode)
		regval |= M98095_DIGMIC_R;

	snd_soc_component_write(component, M98095_087_CFG_MIC, regval);

	/* Configure equalizers */
	if (pdata->eq_cfgcnt)
		max98095_handle_eq_pdata(component);

	/* Configure bi-quad filters */
	if (pdata->bq_cfgcnt)
		max98095_handle_bq_pdata(component);
}