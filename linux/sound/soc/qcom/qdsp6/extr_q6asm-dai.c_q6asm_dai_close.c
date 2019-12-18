#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_1__* dai_link; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; struct snd_soc_pcm_runtime* private_data; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct q6asm_dai_rtd* private_data; } ;
struct q6asm_dai_rtd {int /*<<< orphan*/ * audio_client; scalar_t__ state; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CLOSE ; 
 int /*<<< orphan*/  kfree (struct q6asm_dai_rtd*) ; 
 int /*<<< orphan*/  q6asm_audio_client_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  q6asm_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q6asm_unmap_memory_regions (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  q6routing_stream_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int q6asm_dai_close(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_soc_pcm_runtime *soc_prtd = substream->private_data;
	struct q6asm_dai_rtd *prtd = runtime->private_data;

	if (prtd->audio_client) {
		if (prtd->state)
			q6asm_cmd(prtd->audio_client, CMD_CLOSE);

		q6asm_unmap_memory_regions(substream->stream,
					   prtd->audio_client);
		q6asm_audio_client_free(prtd->audio_client);
		prtd->audio_client = NULL;
	}
	q6routing_stream_close(soc_prtd->dai_link->id,
						substream->stream);
	kfree(prtd);
	return 0;
}