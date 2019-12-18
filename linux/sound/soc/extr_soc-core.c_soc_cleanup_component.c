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
struct snd_soc_component {int /*<<< orphan*/ * card; int /*<<< orphan*/  card_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_module_put_when_remove (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_set_jack (struct snd_soc_component*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_dapm_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_cleanup_component_debugfs (struct snd_soc_component*) ; 

__attribute__((used)) static void soc_cleanup_component(struct snd_soc_component *component)
{
	/* For framework level robustness */
	snd_soc_component_set_jack(component, NULL, NULL);

	list_del_init(&component->card_list);
	snd_soc_dapm_free(snd_soc_component_get_dapm(component));
	soc_cleanup_component_debugfs(component);
	component->card = NULL;
	snd_soc_component_module_put_when_remove(component);
}