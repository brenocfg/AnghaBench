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
struct snd_soc_dai_link {int /*<<< orphan*/  codec_of_node; int /*<<< orphan*/  cpu_of_node; } ;
struct snd_soc_card {int num_links; struct snd_soc_dai_link* dai_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 

int asoc_simple_card_clean_reference(struct snd_soc_card *card)
{
	struct snd_soc_dai_link *dai_link;
	int num_links;

	for (num_links = 0, dai_link = card->dai_link;
	     num_links < card->num_links;
	     num_links++, dai_link++) {
		of_node_put(dai_link->cpu_of_node);
		of_node_put(dai_link->codec_of_node);
	}
	return 0;
}