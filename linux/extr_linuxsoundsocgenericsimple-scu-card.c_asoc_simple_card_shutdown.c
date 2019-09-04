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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  num; int /*<<< orphan*/  card; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct simple_card_data {int dummy; } ;
struct asoc_simple_dai {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  asoc_simple_card_clk_disable (struct asoc_simple_dai*) ; 
 struct asoc_simple_dai* simple_priv_to_props (struct simple_card_data*,int /*<<< orphan*/ ) ; 
 struct simple_card_data* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asoc_simple_card_shutdown(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct simple_card_data *priv =	snd_soc_card_get_drvdata(rtd->card);
	struct asoc_simple_dai *dai_props =
		simple_priv_to_props(priv, rtd->num);

	asoc_simple_card_clk_disable(dai_props);
}