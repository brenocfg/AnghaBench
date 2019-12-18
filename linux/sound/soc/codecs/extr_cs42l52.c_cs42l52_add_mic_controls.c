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
struct snd_soc_component {int dummy; } ;
struct cs42l52_platform_data {int /*<<< orphan*/  micb_diff_cfg; int /*<<< orphan*/  mica_diff_cfg; } ;
struct cs42l52_private {struct cs42l52_platform_data pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs42l52_mica_controls ; 
 int /*<<< orphan*/  cs42l52_micb_controls ; 
 int /*<<< orphan*/  snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cs42l52_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs42l52_add_mic_controls(struct snd_soc_component *component)
{
	struct cs42l52_private *cs42l52 = snd_soc_component_get_drvdata(component);
	struct cs42l52_platform_data *pdata = &cs42l52->pdata;

	if (!pdata->mica_diff_cfg)
		snd_soc_add_component_controls(component, cs42l52_mica_controls,
				     ARRAY_SIZE(cs42l52_mica_controls));

	if (!pdata->micb_diff_cfg)
		snd_soc_add_component_controls(component, cs42l52_micb_controls,
				     ARRAY_SIZE(cs42l52_micb_controls));

	return 0;
}