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
struct snd_soc_component {int /*<<< orphan*/  card_aux_list; int /*<<< orphan*/  init; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; int /*<<< orphan*/  aux_comp_list; struct snd_soc_aux_dev* aux_dev; } ;
struct snd_soc_aux_dev {char* codec_name; char* name; int /*<<< orphan*/  init; struct device_node* codec_of_node; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* of_node_full_name (struct device_node*) ; 
 struct snd_soc_component* soc_find_component (struct device_node*,char const*) ; 

__attribute__((used)) static int soc_bind_aux_dev(struct snd_soc_card *card, int num)
{
	struct snd_soc_aux_dev *aux_dev = &card->aux_dev[num];
	struct snd_soc_component *component;
	const char *name;
	struct device_node *codec_of_node;

	if (aux_dev->codec_of_node || aux_dev->codec_name) {
		/* codecs, usually analog devices */
		name = aux_dev->codec_name;
		codec_of_node = aux_dev->codec_of_node;
		component = soc_find_component(codec_of_node, name);
		if (!component) {
			if (codec_of_node)
				name = of_node_full_name(codec_of_node);
			goto err_defer;
		}
	} else if (aux_dev->name) {
		/* generic components */
		name = aux_dev->name;
		component = soc_find_component(NULL, name);
		if (!component)
			goto err_defer;
	} else {
		dev_err(card->dev, "ASoC: Invalid auxiliary device\n");
		return -EINVAL;
	}

	component->init = aux_dev->init;
	list_add(&component->card_aux_list, &card->aux_comp_list);

	return 0;

err_defer:
	dev_err(card->dev, "ASoC: %s not registered\n", name);
	return -EPROBE_DEFER;
}