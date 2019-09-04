#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai_link {int num_codecs; TYPE_1__* codecs; int /*<<< orphan*/  cpu_of_node; } ;
struct snd_soc_card {int num_links; int num_aux_devs; struct snd_soc_dai_link* dai_link; TYPE_2__* aux_dev; } ;
struct axg_card {struct snd_soc_dai_link* link_data; struct snd_soc_card card; } ;
struct TYPE_4__ {int /*<<< orphan*/  codec_of_node; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_soc_dai_link*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void axg_card_clean_references(struct axg_card *priv)
{
	struct snd_soc_card *card = &priv->card;
	struct snd_soc_dai_link *link;
	int i, j;

	if (card->dai_link) {
		for (i = 0; i < card->num_links; i++) {
			link = &card->dai_link[i];
			of_node_put(link->cpu_of_node);
			for (j = 0; j < link->num_codecs; j++)
				of_node_put(link->codecs[j].of_node);
		}
	}

	if (card->aux_dev) {
		for (i = 0; i < card->num_aux_devs; i++)
			of_node_put(card->aux_dev[i].codec_of_node);
	}

	kfree(card->dai_link);
	kfree(priv->link_data);
}