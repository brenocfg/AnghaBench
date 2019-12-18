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
struct snd_soc_component {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_soc_component_remove (struct snd_soc_component*) ; 
 int /*<<< orphan*/  soc_cleanup_component (struct snd_soc_component*) ; 

__attribute__((used)) static void soc_remove_component(struct snd_soc_component *component)
{
	if (!component->card)
		return;

	snd_soc_component_remove(component);

	soc_cleanup_component(component);
}