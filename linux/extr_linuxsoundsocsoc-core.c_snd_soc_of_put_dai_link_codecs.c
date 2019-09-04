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
struct snd_soc_dai_link_component {int /*<<< orphan*/ * of_node; } ;
struct snd_soc_dai_link {int num_codecs; struct snd_soc_dai_link_component* codecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ *) ; 

void snd_soc_of_put_dai_link_codecs(struct snd_soc_dai_link *dai_link)
{
	struct snd_soc_dai_link_component *component = dai_link->codecs;
	int index;

	for (index = 0; index < dai_link->num_codecs; index++, component++) {
		if (!component->of_node)
			break;
		of_node_put(component->of_node);
		component->of_node = NULL;
	}
}