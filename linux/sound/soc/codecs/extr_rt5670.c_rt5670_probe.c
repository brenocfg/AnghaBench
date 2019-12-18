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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct rt5670_priv {struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
#define  RT5670_ID_5670 130 
#define  RT5670_ID_5671 129 
#define  RT5670_ID_5672 128 
 int RT5670_ID_MASK ; 
 int /*<<< orphan*/  RT5670_RESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rt5670_specific_dapm_routes ; 
 int /*<<< orphan*/  rt5670_specific_dapm_widgets ; 
 int /*<<< orphan*/  rt5672_specific_dapm_routes ; 
 int /*<<< orphan*/  rt5672_specific_dapm_widgets ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct rt5670_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5670_probe(struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);

	switch (snd_soc_component_read32(component, RT5670_RESET) & RT5670_ID_MASK) {
	case RT5670_ID_5670:
	case RT5670_ID_5671:
		snd_soc_dapm_new_controls(dapm,
			rt5670_specific_dapm_widgets,
			ARRAY_SIZE(rt5670_specific_dapm_widgets));
		snd_soc_dapm_add_routes(dapm,
			rt5670_specific_dapm_routes,
			ARRAY_SIZE(rt5670_specific_dapm_routes));
		break;
	case RT5670_ID_5672:
		snd_soc_dapm_new_controls(dapm,
			rt5672_specific_dapm_widgets,
			ARRAY_SIZE(rt5672_specific_dapm_widgets));
		snd_soc_dapm_add_routes(dapm,
			rt5672_specific_dapm_routes,
			ARRAY_SIZE(rt5672_specific_dapm_routes));
		break;
	default:
		dev_err(component->dev,
			"The driver is for RT5670 RT5671 or RT5672 only\n");
		return -ENODEV;
	}
	rt5670->component = component;

	return 0;
}