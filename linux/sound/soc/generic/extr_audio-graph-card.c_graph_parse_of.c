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
struct snd_soc_card {int dummy; } ;
struct link_info {int cpu; } ;
struct asoc_simple_priv {int dummy; } ;
typedef  int /*<<< orphan*/  li ;

/* Variables and functions */
 int asoc_simple_parse_card_name (struct snd_soc_card*,int /*<<< orphan*/ *) ; 
 int asoc_simple_parse_routing (struct snd_soc_card*,int /*<<< orphan*/ *) ; 
 int asoc_simple_parse_widgets (struct snd_soc_card*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  graph_dai_link_of ; 
 int /*<<< orphan*/  graph_dai_link_of_dpcm ; 
 int graph_for_each_link (struct asoc_simple_priv*,struct link_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct link_info*,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_card* simple_priv_to_card (struct asoc_simple_priv*) ; 

__attribute__((used)) static int graph_parse_of(struct asoc_simple_priv *priv)
{
	struct snd_soc_card *card = simple_priv_to_card(priv);
	struct link_info li;
	int ret;

	ret = asoc_simple_parse_widgets(card, NULL);
	if (ret < 0)
		return ret;

	ret = asoc_simple_parse_routing(card, NULL);
	if (ret < 0)
		return ret;

	memset(&li, 0, sizeof(li));
	for (li.cpu = 1; li.cpu >= 0; li.cpu--) {
		/*
		 * Detect all CPU first, and Detect all Codec 2nd.
		 *
		 * In Normal sound case, all DAIs are detected
		 * as "CPU-Codec".
		 *
		 * In DPCM sound case,
		 * all CPUs   are detected as "CPU-dummy", and
		 * all Codecs are detected as "dummy-Codec".
		 * To avoid random sub-device numbering,
		 * detect "dummy-Codec" in last;
		 */
		ret = graph_for_each_link(priv, &li,
					  graph_dai_link_of,
					  graph_dai_link_of_dpcm);
		if (ret < 0)
			return ret;
	}

	return asoc_simple_parse_card_name(card, NULL);
}