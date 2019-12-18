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
struct simple_dai_props {int /*<<< orphan*/  cpu_dai; int /*<<< orphan*/  codec_dai; } ;
struct asoc_simple_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  asoc_simple_clk_disable (int /*<<< orphan*/ ) ; 
 int asoc_simple_clk_enable (int /*<<< orphan*/ ) ; 
 struct simple_dai_props* simple_priv_to_props (struct asoc_simple_priv*,int /*<<< orphan*/ ) ; 
 struct asoc_simple_priv* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 

int asoc_simple_startup(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct asoc_simple_priv *priv = snd_soc_card_get_drvdata(rtd->card);
	struct simple_dai_props *dai_props = simple_priv_to_props(priv, rtd->num);
	int ret;

	ret = asoc_simple_clk_enable(dai_props->cpu_dai);
	if (ret)
		return ret;

	ret = asoc_simple_clk_enable(dai_props->codec_dai);
	if (ret)
		asoc_simple_clk_disable(dai_props->cpu_dai);

	return ret;
}