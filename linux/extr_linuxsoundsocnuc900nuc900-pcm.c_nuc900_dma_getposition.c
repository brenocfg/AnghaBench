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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct nuc900_audio* private_data; } ;
struct nuc900_audio {scalar_t__ mmio; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ ACTL_PDSTC ; 
 scalar_t__ ACTL_RDSTC ; 
 int /*<<< orphan*/  AUDIO_READ (scalar_t__) ; 

__attribute__((used)) static int nuc900_dma_getposition(struct snd_pcm_substream *substream,
					dma_addr_t *src, dma_addr_t *dst)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct nuc900_audio *nuc900_audio = runtime->private_data;

	if (src != NULL)
		*src = AUDIO_READ(nuc900_audio->mmio + ACTL_PDSTC);

	if (dst != NULL)
		*dst = AUDIO_READ(nuc900_audio->mmio + ACTL_RDSTC);

	return 0;
}