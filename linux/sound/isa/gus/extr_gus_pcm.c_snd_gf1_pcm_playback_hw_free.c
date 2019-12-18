#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct gus_pcm_private* private_data; } ;
struct gus_pcm_private {scalar_t__ memory; TYPE_2__* gus; int /*<<< orphan*/ ** pvoices; } ;
struct TYPE_3__ {int /*<<< orphan*/  mem_alloc; } ;
struct TYPE_4__ {TYPE_1__ gf1; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_gf1_free_voice (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_gf1_mem_free (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_gf1_pcm_playback_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct gus_pcm_private *pcmp = runtime->private_data;

	snd_pcm_lib_free_pages(substream);
	if (pcmp->pvoices[0]) {
		snd_gf1_free_voice(pcmp->gus, pcmp->pvoices[0]);
		pcmp->pvoices[0] = NULL;
	}
	if (pcmp->pvoices[1]) {
		snd_gf1_free_voice(pcmp->gus, pcmp->pvoices[1]);
		pcmp->pvoices[1] = NULL;
	}
	if (pcmp->memory > 0) {
		snd_gf1_mem_free(&pcmp->gus->gf1.mem_alloc, pcmp->memory);
		pcmp->memory = 0;
	}
	return 0;
}