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
struct snd_pcm_substream {int dummy; } ;
struct snd_gus_card {int /*<<< orphan*/ * pcm_cap_substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_GF1_HANDLER_DMA_READ ; 
 int /*<<< orphan*/  snd_gf1_set_default_handlers (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 struct snd_gus_card* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_gf1_pcm_capture_close(struct snd_pcm_substream *substream)
{
	struct snd_gus_card *gus = snd_pcm_substream_chip(substream);

	gus->pcm_cap_substream = NULL;
	snd_gf1_set_default_handlers(gus, SNDRV_GF1_HANDLER_DMA_READ);
	return 0;
}