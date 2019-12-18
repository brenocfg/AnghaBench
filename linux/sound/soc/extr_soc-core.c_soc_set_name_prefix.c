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
struct snd_soc_component {int /*<<< orphan*/  name_prefix; int /*<<< orphan*/  name; } ;
struct snd_soc_codec_conf {int /*<<< orphan*/  name_prefix; scalar_t__ dev_name; struct device_node* of_node; } ;
struct snd_soc_card {int num_configs; struct snd_soc_codec_conf* codec_conf; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* soc_component_to_node (struct snd_soc_component*) ; 
 int /*<<< orphan*/  soc_set_of_name_prefix (struct snd_soc_component*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void soc_set_name_prefix(struct snd_soc_card *card,
				struct snd_soc_component *component)
{
	int i;

	for (i = 0; i < card->num_configs && card->codec_conf; i++) {
		struct snd_soc_codec_conf *map = &card->codec_conf[i];
		struct device_node *of_node = soc_component_to_node(component);

		if (map->of_node && of_node != map->of_node)
			continue;
		if (map->dev_name && strcmp(component->name, map->dev_name))
			continue;
		component->name_prefix = map->name_prefix;
		return;
	}

	/*
	 * If there is no configuration table or no match in the table,
	 * check if a prefix is provided in the node
	 */
	soc_set_of_name_prefix(component);
}