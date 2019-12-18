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
struct aaci_runtime {int cr; scalar_t__ pcm_open; int /*<<< orphan*/  pcm; } ;
struct TYPE_2__ {struct aaci_runtime* private_data; } ;

/* Variables and functions */
 int CR_EN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  snd_ac97_pcm_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 

__attribute__((used)) static int aaci_pcm_hw_free(struct snd_pcm_substream *substream)
{
	struct aaci_runtime *aacirun = substream->runtime->private_data;

	/*
	 * This must not be called with the device enabled.
	 */
	WARN_ON(aacirun->cr & CR_EN);

	if (aacirun->pcm_open)
		snd_ac97_pcm_close(aacirun->pcm);
	aacirun->pcm_open = 0;

	/*
	 * Clear out the DMA and any allocated buffers.
	 */
	snd_pcm_lib_free_pages(substream);

	return 0;
}