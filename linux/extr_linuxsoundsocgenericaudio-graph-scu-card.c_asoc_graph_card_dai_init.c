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
struct snd_soc_pcm_runtime {int num; struct snd_soc_dai* codec_dai; struct snd_soc_dai* cpu_dai; int /*<<< orphan*/  card; } ;
struct snd_soc_dai_link {scalar_t__ dynamic; } ;
struct snd_soc_dai {int dummy; } ;
struct graph_card_data {int dummy; } ;
struct asoc_simple_dai {int dummy; } ;

/* Variables and functions */
 int asoc_simple_card_init_dai (struct snd_soc_dai*,struct asoc_simple_dai*) ; 
 struct snd_soc_dai_link* graph_priv_to_link (struct graph_card_data*,int) ; 
 struct asoc_simple_dai* graph_priv_to_props (struct graph_card_data*,int) ; 
 struct graph_card_data* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asoc_graph_card_dai_init(struct snd_soc_pcm_runtime *rtd)
{
	struct graph_card_data *priv =	snd_soc_card_get_drvdata(rtd->card);
	struct snd_soc_dai *dai;
	struct snd_soc_dai_link *dai_link;
	struct asoc_simple_dai *dai_props;
	int num = rtd->num;

	dai_link	= graph_priv_to_link(priv, num);
	dai_props	= graph_priv_to_props(priv, num);
	dai		= dai_link->dynamic ?
				rtd->cpu_dai :
				rtd->codec_dai;

	return asoc_simple_card_init_dai(dai, dai_props);
}