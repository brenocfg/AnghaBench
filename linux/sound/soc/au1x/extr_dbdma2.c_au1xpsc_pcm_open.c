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
struct snd_pcm_substream {int stream; struct snd_soc_pcm_runtime* private_data; } ;
struct au1xpsc_audio_dmadata {int ddma_id; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  au1xpsc_pcm_hardware ; 
 int* snd_soc_dai_get_dma_data (int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_soc_set_runtime_hwparams (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 struct au1xpsc_audio_dmadata* to_dmadata (struct snd_pcm_substream*) ; 

__attribute__((used)) static int au1xpsc_pcm_open(struct snd_pcm_substream *substream)
{
	struct au1xpsc_audio_dmadata *pcd = to_dmadata(substream);
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	int stype = substream->stream, *dmaids;

	dmaids = snd_soc_dai_get_dma_data(rtd->cpu_dai, substream);
	if (!dmaids)
		return -ENODEV;	/* whoa, has ordering changed? */

	pcd->ddma_id = dmaids[stype];

	snd_soc_set_runtime_hwparams(substream, &au1xpsc_pcm_hardware);
	return 0;
}