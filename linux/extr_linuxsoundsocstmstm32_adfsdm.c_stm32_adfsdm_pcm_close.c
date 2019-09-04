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
struct stm32_adfsdm_priv {int /*<<< orphan*/ * substream; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 struct stm32_adfsdm_priv* snd_soc_dai_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_adfsdm_pcm_close(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct stm32_adfsdm_priv *priv =
		snd_soc_dai_get_drvdata(rtd->cpu_dai);

	snd_pcm_lib_free_pages(substream);
	priv->substream = NULL;

	return 0;
}