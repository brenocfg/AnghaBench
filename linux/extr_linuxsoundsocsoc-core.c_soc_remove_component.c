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
struct snd_soc_component {TYPE_3__* dev; int /*<<< orphan*/ * card; TYPE_1__* driver; int /*<<< orphan*/  card_list; } ;
struct TYPE_6__ {TYPE_2__* driver; } ;
struct TYPE_5__ {int /*<<< orphan*/  owner; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* remove ) (struct snd_soc_component*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_cleanup_component_debugfs (struct snd_soc_component*) ; 
 int /*<<< orphan*/  stub1 (struct snd_soc_component*) ; 

__attribute__((used)) static void soc_remove_component(struct snd_soc_component *component)
{
	if (!component->card)
		return;

	list_del(&component->card_list);

	if (component->driver->remove)
		component->driver->remove(component);

	snd_soc_dapm_free(snd_soc_component_get_dapm(component));

	soc_cleanup_component_debugfs(component);
	component->card = NULL;
	module_put(component->dev->driver->owner);
}