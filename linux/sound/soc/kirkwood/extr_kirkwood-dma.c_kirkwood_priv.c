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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct kirkwood_dma_data {int dummy; } ;

/* Variables and functions */
 struct kirkwood_dma_data* snd_soc_dai_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct kirkwood_dma_data *kirkwood_priv(struct snd_pcm_substream *subs)
{
	struct snd_soc_pcm_runtime *soc_runtime = subs->private_data;
	return snd_soc_dai_get_drvdata(soc_runtime->cpu_dai);
}