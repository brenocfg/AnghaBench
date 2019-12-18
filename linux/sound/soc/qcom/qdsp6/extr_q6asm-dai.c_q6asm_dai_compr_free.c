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
struct snd_compr_stream {int /*<<< orphan*/  direction; struct snd_soc_pcm_runtime* private_data; struct snd_compr_runtime* runtime; } ;
struct snd_compr_runtime {struct q6asm_dai_rtd* private_data; } ;
struct q6asm_dai_rtd {int /*<<< orphan*/ * audio_client; int /*<<< orphan*/  dma_buffer; scalar_t__ state; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CLOSE ; 
 int /*<<< orphan*/  kfree (struct q6asm_dai_rtd*) ; 
 int /*<<< orphan*/  q6asm_audio_client_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  q6asm_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q6asm_unmap_memory_regions (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  q6routing_stream_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_dma_free_pages (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int q6asm_dai_compr_free(struct snd_compr_stream *stream)
{
	struct snd_compr_runtime *runtime = stream->runtime;
	struct q6asm_dai_rtd *prtd = runtime->private_data;
	struct snd_soc_pcm_runtime *rtd = stream->private_data;

	if (prtd->audio_client) {
		if (prtd->state)
			q6asm_cmd(prtd->audio_client, CMD_CLOSE);

		snd_dma_free_pages(&prtd->dma_buffer);
		q6asm_unmap_memory_regions(stream->direction,
					   prtd->audio_client);
		q6asm_audio_client_free(prtd->audio_client);
		prtd->audio_client = NULL;
	}
	q6routing_stream_close(rtd->dai_link->id, stream->direction);
	kfree(prtd);

	return 0;
}