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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  num; struct snd_soc_dai* cpu_dai; struct snd_soc_dai* codec_dai; int /*<<< orphan*/  card; } ;
struct snd_soc_dai {int dummy; } ;
struct simple_dai_props {int /*<<< orphan*/  cpu_dai; int /*<<< orphan*/  codec_dai; } ;
struct simple_card_data {int dummy; } ;

/* Variables and functions */
 int asoc_simple_card_init_dai (struct snd_soc_dai*,int /*<<< orphan*/ *) ; 
 struct simple_dai_props* simple_priv_to_props (struct simple_card_data*,int /*<<< orphan*/ ) ; 
 struct simple_card_data* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asoc_simple_card_dai_init(struct snd_soc_pcm_runtime *rtd)
{
	struct simple_card_data *priv =	snd_soc_card_get_drvdata(rtd->card);
	struct snd_soc_dai *codec = rtd->codec_dai;
	struct snd_soc_dai *cpu = rtd->cpu_dai;
	struct simple_dai_props *dai_props =
		simple_priv_to_props(priv, rtd->num);
	int ret;

	ret = asoc_simple_card_init_dai(codec, &dai_props->codec_dai);
	if (ret < 0)
		return ret;

	ret = asoc_simple_card_init_dai(cpu, &dai_props->cpu_dai);
	if (ret < 0)
		return ret;

	return 0;
}