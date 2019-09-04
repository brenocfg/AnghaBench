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
struct tas2552_data {int /*<<< orphan*/  enable_gpio; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 struct tas2552_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void tas2552_component_remove(struct snd_soc_component *component)
{
	struct tas2552_data *tas2552 = snd_soc_component_get_drvdata(component);

	pm_runtime_put(component->dev);

	gpiod_set_value(tas2552->enable_gpio, 0);
}