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
struct TYPE_2__ {int dma_shared; int /*<<< orphan*/ * dma_data_synth_last; int /*<<< orphan*/  dma_data_synth; int /*<<< orphan*/  dma_data_pcm_last; int /*<<< orphan*/  dma_data_pcm; int /*<<< orphan*/  interrupt_handler_dma_write; } ;
struct snd_gus_card {int /*<<< orphan*/  dma_mutex; TYPE_1__ gf1; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_gf1_dma_interrupt ; 

int snd_gf1_dma_init(struct snd_gus_card * gus)
{
	mutex_lock(&gus->dma_mutex);
	gus->gf1.dma_shared++;
	if (gus->gf1.dma_shared > 1) {
		mutex_unlock(&gus->dma_mutex);
		return 0;
	}
	gus->gf1.interrupt_handler_dma_write = snd_gf1_dma_interrupt;
	gus->gf1.dma_data_pcm = 
	gus->gf1.dma_data_pcm_last =
	gus->gf1.dma_data_synth = 
	gus->gf1.dma_data_synth_last = NULL;
	mutex_unlock(&gus->dma_mutex);
	return 0;
}