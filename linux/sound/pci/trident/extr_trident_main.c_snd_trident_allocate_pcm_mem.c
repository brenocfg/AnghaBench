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
struct snd_trident_voice {int /*<<< orphan*/ * memblk; } ;
struct TYPE_2__ {scalar_t__ entries; } ;
struct snd_trident {TYPE_1__ tlb; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct snd_trident_voice* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct snd_trident* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/ * snd_trident_alloc_pages (struct snd_trident*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_trident_free_pages (struct snd_trident*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_trident_allocate_pcm_mem(struct snd_pcm_substream *substream,
					struct snd_pcm_hw_params *hw_params)
{
	struct snd_trident *trident = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_trident_voice *voice = runtime->private_data;
	int err;

	if ((err = snd_pcm_lib_malloc_pages(substream, params_buffer_bytes(hw_params))) < 0)
		return err;
	if (trident->tlb.entries) {
		if (err > 0) { /* change */
			if (voice->memblk)
				snd_trident_free_pages(trident, voice->memblk);
			voice->memblk = snd_trident_alloc_pages(trident, substream);
			if (voice->memblk == NULL)
				return -ENOMEM;
		}
	}
	return 0;
}