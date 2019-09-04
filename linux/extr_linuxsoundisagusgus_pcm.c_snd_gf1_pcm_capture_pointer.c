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
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma2; } ;
struct snd_gus_card {int c_pos; int c_dma_size; int /*<<< orphan*/  c_period_size; TYPE_1__ gf1; } ;
typedef  int snd_pcm_uframes_t ;

/* Variables and functions */
 int bytes_to_frames (int /*<<< orphan*/ ,int) ; 
 int snd_dma_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_gus_card* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_gf1_pcm_capture_pointer(struct snd_pcm_substream *substream)
{
	struct snd_gus_card *gus = snd_pcm_substream_chip(substream);
	int pos = snd_dma_pointer(gus->gf1.dma2, gus->c_period_size);
	pos = bytes_to_frames(substream->runtime, (gus->c_pos + pos) % gus->c_dma_size);
	return pos;
}