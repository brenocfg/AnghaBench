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
struct stm32_adfsdm_priv {struct snd_pcm_substream* substream; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;

/* Variables and functions */
 struct stm32_adfsdm_priv* snd_soc_dai_get_drvdata (int /*<<< orphan*/ ) ; 
 int snd_soc_set_runtime_hwparams (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_adfsdm_pcm_hw ; 

__attribute__((used)) static int stm32_adfsdm_pcm_open(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct stm32_adfsdm_priv *priv = snd_soc_dai_get_drvdata(rtd->cpu_dai);
	int ret;

	ret =  snd_soc_set_runtime_hwparams(substream, &stm32_adfsdm_pcm_hw);
	if (!ret)
		priv->substream = substream;

	return ret;
}