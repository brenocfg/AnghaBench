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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; int /*<<< orphan*/  codec_dai; int /*<<< orphan*/  num; int /*<<< orphan*/  card; } ;
struct simple_dai_props {int /*<<< orphan*/  cpu_dai; int /*<<< orphan*/  codec_dai; } ;
struct asoc_simple_priv {int dummy; } ;

/* Variables and functions */
 int asoc_simple_init_dai (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct simple_dai_props* simple_priv_to_props (struct asoc_simple_priv*,int /*<<< orphan*/ ) ; 
 struct asoc_simple_priv* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 

int asoc_simple_dai_init(struct snd_soc_pcm_runtime *rtd)
{
	struct asoc_simple_priv *priv = snd_soc_card_get_drvdata(rtd->card);
	struct simple_dai_props *dai_props = simple_priv_to_props(priv, rtd->num);
	int ret;

	ret = asoc_simple_init_dai(rtd->codec_dai,
				   dai_props->codec_dai);
	if (ret < 0)
		return ret;

	ret = asoc_simple_init_dai(rtd->cpu_dai,
				   dai_props->cpu_dai);
	if (ret < 0)
		return ret;

	return 0;
}