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
struct snd_pcm_runtime {scalar_t__ dma_area; struct aaci_runtime* private_data; } ;
struct aaci_runtime {int /*<<< orphan*/  period; int /*<<< orphan*/  bytes; scalar_t__ start; scalar_t__ ptr; scalar_t__ end; } ;

/* Variables and functions */
 scalar_t__ snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 

__attribute__((used)) static int aaci_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct aaci_runtime *aacirun = runtime->private_data;

	aacirun->period	= snd_pcm_lib_period_bytes(substream);
	aacirun->start	= runtime->dma_area;
	aacirun->end	= aacirun->start + snd_pcm_lib_buffer_bytes(substream);
	aacirun->ptr	= aacirun->start;
	aacirun->bytes	= aacirun->period;

	return 0;
}