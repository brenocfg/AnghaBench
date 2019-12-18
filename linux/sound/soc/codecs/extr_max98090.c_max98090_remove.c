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
struct max98090_priv {int /*<<< orphan*/ * component; int /*<<< orphan*/  pll_work; int /*<<< orphan*/  pll_det_disable_work; int /*<<< orphan*/  pll_det_enable_work; int /*<<< orphan*/  jack_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct max98090_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void max98090_remove(struct snd_soc_component *component)
{
	struct max98090_priv *max98090 = snd_soc_component_get_drvdata(component);

	cancel_delayed_work_sync(&max98090->jack_work);
	cancel_delayed_work_sync(&max98090->pll_det_enable_work);
	cancel_work_sync(&max98090->pll_det_disable_work);
	cancel_work_sync(&max98090->pll_work);
	max98090->component = NULL;
}