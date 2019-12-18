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
struct madera {int /*<<< orphan*/  dapm_ptr_lock; int /*<<< orphan*/ * dapm; } ;
struct TYPE_2__ {int /*<<< orphan*/ * adsp; struct madera* madera; } ;
struct cs47l92 {TYPE_1__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cs47l92* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm_adsp2_component_remove (int /*<<< orphan*/ *,struct snd_soc_component*) ; 

__attribute__((used)) static void cs47l92_component_remove(struct snd_soc_component *component)
{
	struct cs47l92 *cs47l92 = snd_soc_component_get_drvdata(component);
	struct madera *madera = cs47l92->core.madera;

	mutex_lock(&madera->dapm_ptr_lock);
	madera->dapm = NULL;
	mutex_unlock(&madera->dapm_ptr_lock);

	wm_adsp2_component_remove(&cs47l92->core.adsp[0], component);
}