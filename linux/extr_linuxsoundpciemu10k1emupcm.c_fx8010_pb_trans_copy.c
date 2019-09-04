#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {size_t number; TYPE_1__* runtime; } ;
struct snd_pcm_indirect {scalar_t__ sw_data; } ;
struct snd_emu10k1_fx8010_pcm {unsigned int buffer_size; unsigned int tram_pos; unsigned int tram_shift; } ;
struct TYPE_5__ {scalar_t__ area; } ;
struct TYPE_6__ {TYPE_2__ etram_pages; struct snd_emu10k1_fx8010_pcm* pcm; } ;
struct snd_emu10k1 {TYPE_3__ fx8010; } ;
struct TYPE_4__ {scalar_t__ dma_area; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_emu10k1_fx8010_playback_tram_poke1 (unsigned short*,unsigned short*,unsigned short*,unsigned int,unsigned int) ; 
 struct snd_emu10k1* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static void fx8010_pb_trans_copy(struct snd_pcm_substream *substream,
				 struct snd_pcm_indirect *rec, size_t bytes)
{
	struct snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	struct snd_emu10k1_fx8010_pcm *pcm = &emu->fx8010.pcm[substream->number];
	unsigned int tram_size = pcm->buffer_size;
	unsigned short *src = (unsigned short *)(substream->runtime->dma_area + rec->sw_data);
	unsigned int frames = bytes >> 2, count;
	unsigned int tram_pos = pcm->tram_pos;
	unsigned int tram_shift = pcm->tram_shift;

	while (frames > tram_pos) {
		count = tram_pos + 1;
		snd_emu10k1_fx8010_playback_tram_poke1((unsigned short *)emu->fx8010.etram_pages.area + tram_pos,
						       (unsigned short *)emu->fx8010.etram_pages.area + tram_pos + tram_size / 2,
						       src, count, tram_shift);
		src += count * 2;
		frames -= count;
		tram_pos = (tram_size / 2) - 1;
		tram_shift++;
	}
	snd_emu10k1_fx8010_playback_tram_poke1((unsigned short *)emu->fx8010.etram_pages.area + tram_pos,
					       (unsigned short *)emu->fx8010.etram_pages.area + tram_pos + tram_size / 2,
					       src, frames, tram_shift);
	tram_pos -= frames;
	pcm->tram_pos = tram_pos;
	pcm->tram_shift = tram_shift;
}