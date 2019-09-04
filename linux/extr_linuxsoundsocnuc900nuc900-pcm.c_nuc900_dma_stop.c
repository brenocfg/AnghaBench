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

/* Variables and functions */
 scalar_t__ ACTL_CON ; 
 unsigned long AUDIO_READ (scalar_t__) ; 
 int /*<<< orphan*/  AUDIO_WRITE (scalar_t__,unsigned long) ; 
 unsigned long R_DMA_IRQ ; 
 unsigned long T_DMA_IRQ ; 

__attribute__((used)) static void nuc900_dma_stop(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct nuc900_audio *nuc900_audio = runtime->private_data;
	unsigned long val;

	val = AUDIO_READ(nuc900_audio->mmio + ACTL_CON);
	val &= ~(T_DMA_IRQ | R_DMA_IRQ);
	AUDIO_WRITE(nuc900_audio->mmio + ACTL_CON, val);
}