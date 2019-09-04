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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol_new {int dummy; } ;
struct TYPE_2__ {char const** texts; size_t items; } ;
struct max98095_priv {int eq_textcnt; char const** eq_texts; TYPE_1__ eq_enum; struct max98095_pdata* pdata; } ;
struct max98095_pdata {unsigned int eq_cfgcnt; struct max98095_eq_cfg* eq_cfg; } ;
struct max98095_eq_cfg {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct snd_kcontrol_new*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct snd_kcontrol_new SOC_ENUM_EXT (char*,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 char** krealloc (char const**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max98095_get_eq_enum ; 
 int /*<<< orphan*/  max98095_put_eq_enum ; 
 int snd_soc_add_component_controls (struct snd_soc_component*,struct snd_kcontrol_new*,int /*<<< orphan*/ ) ; 
 struct max98095_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static void max98095_handle_eq_pdata(struct snd_soc_component *component)
{
	struct max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	struct max98095_pdata *pdata = max98095->pdata;
	struct max98095_eq_cfg *cfg;
	unsigned int cfgcnt;
	int i, j;
	const char **t;
	int ret;

	struct snd_kcontrol_new controls[] = {
		SOC_ENUM_EXT("EQ1 Mode",
			max98095->eq_enum,
			max98095_get_eq_enum,
			max98095_put_eq_enum),
		SOC_ENUM_EXT("EQ2 Mode",
			max98095->eq_enum,
			max98095_get_eq_enum,
			max98095_put_eq_enum),
	};

	cfg = pdata->eq_cfg;
	cfgcnt = pdata->eq_cfgcnt;

	/* Setup an array of texts for the equalizer enum.
	 * This is based on Mark Brown's equalizer driver code.
	 */
	max98095->eq_textcnt = 0;
	max98095->eq_texts = NULL;
	for (i = 0; i < cfgcnt; i++) {
		for (j = 0; j < max98095->eq_textcnt; j++) {
			if (strcmp(cfg[i].name, max98095->eq_texts[j]) == 0)
				break;
		}

		if (j != max98095->eq_textcnt)
			continue;

		/* Expand the array */
		t = krealloc(max98095->eq_texts,
			     sizeof(char *) * (max98095->eq_textcnt + 1),
			     GFP_KERNEL);
		if (t == NULL)
			continue;

		/* Store the new entry */
		t[max98095->eq_textcnt] = cfg[i].name;
		max98095->eq_textcnt++;
		max98095->eq_texts = t;
	}

	/* Now point the soc_enum to .texts array items */
	max98095->eq_enum.texts = max98095->eq_texts;
	max98095->eq_enum.items = max98095->eq_textcnt;

	ret = snd_soc_add_component_controls(component, controls, ARRAY_SIZE(controls));
	if (ret != 0)
		dev_err(component->dev, "Failed to add EQ control: %d\n", ret);
}