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
struct snd_soc_component {int /*<<< orphan*/  list; scalar_t__ regmap; int /*<<< orphan*/  dev; TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  read; int /*<<< orphan*/  write; } ;

/* Variables and functions */
 int /*<<< orphan*/  client_mutex ; 
 int /*<<< orphan*/  component_list ; 
 scalar_t__ dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_component_setup_regmap (struct snd_soc_component*) ; 

__attribute__((used)) static void snd_soc_component_add(struct snd_soc_component *component)
{
	mutex_lock(&client_mutex);

	if (!component->driver->write && !component->driver->read) {
		if (!component->regmap)
			component->regmap = dev_get_regmap(component->dev,
							   NULL);
		if (component->regmap)
			snd_soc_component_setup_regmap(component);
	}

	/* see for_each_component */
	list_add(&component->list, &component_list);

	mutex_unlock(&client_mutex);
}