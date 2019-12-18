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
struct snd_soc_dai {int /*<<< orphan*/  active; } ;
struct snd_pcm_substream {size_t stream; } ;
struct davinci_mcasp {scalar_t__ op_mode; scalar_t__ max_format_width; scalar_t__ channels; scalar_t__* active_serializers; int /*<<< orphan*/ ** substreams; } ;

/* Variables and functions */
 scalar_t__ DAVINCI_MCASP_DIT_MODE ; 
 struct davinci_mcasp* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static void davinci_mcasp_shutdown(struct snd_pcm_substream *substream,
				   struct snd_soc_dai *cpu_dai)
{
	struct davinci_mcasp *mcasp = snd_soc_dai_get_drvdata(cpu_dai);

	mcasp->substreams[substream->stream] = NULL;
	mcasp->active_serializers[substream->stream] = 0;

	if (mcasp->op_mode == DAVINCI_MCASP_DIT_MODE)
		return;

	if (!cpu_dai->active) {
		mcasp->channels = 0;
		mcasp->max_format_width = 0;
	}
}