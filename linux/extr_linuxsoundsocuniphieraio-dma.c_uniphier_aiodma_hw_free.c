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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct TYPE_2__ {scalar_t__ dma_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_set_runtime_buffer (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uniphier_aiodma_hw_free(struct snd_pcm_substream *substream)
{
	snd_pcm_set_runtime_buffer(substream, NULL);
	substream->runtime->dma_bytes = 0;

	return 0;
}