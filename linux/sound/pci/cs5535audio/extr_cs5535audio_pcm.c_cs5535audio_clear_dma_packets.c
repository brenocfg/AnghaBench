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
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * area; } ;
struct cs5535audio_dma {int /*<<< orphan*/ * substream; TYPE_1__ desc_buf; } ;
struct cs5535audio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_1__*) ; 

__attribute__((used)) static void cs5535audio_clear_dma_packets(struct cs5535audio *cs5535au,
					  struct cs5535audio_dma *dma,
					  struct snd_pcm_substream *substream)
{
	snd_dma_free_pages(&dma->desc_buf);
	dma->desc_buf.area = NULL;
	dma->substream = NULL;
}