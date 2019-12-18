#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int periods; int dma_addr; int /*<<< orphan*/  period_size; struct emu10k1x_pcm* private_data; } ;
struct emu10k1x_pcm {TYPE_1__* voice; } ;
struct TYPE_4__ {int addr; scalar_t__ area; } ;
struct emu10k1x {TYPE_2__ dma_buffer; } ;
struct TYPE_3__ {int number; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLAYBACK_DMA_ADDR ; 
 int /*<<< orphan*/  PLAYBACK_LIST_ADDR ; 
 int /*<<< orphan*/  PLAYBACK_LIST_PTR ; 
 int /*<<< orphan*/  PLAYBACK_LIST_SIZE ; 
 int /*<<< orphan*/  PLAYBACK_PERIOD_SIZE ; 
 int /*<<< orphan*/  PLAYBACK_POINTER ; 
 int /*<<< orphan*/  PLAYBACK_UNKNOWN1 ; 
 int /*<<< orphan*/  PLAYBACK_UNKNOWN2 ; 
 int frames_to_bytes (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1x_ptr_write (struct emu10k1x*,int /*<<< orphan*/ ,int,int) ; 
 struct emu10k1x* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_emu10k1x_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct emu10k1x *emu = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct emu10k1x_pcm *epcm = runtime->private_data;
	int voice = epcm->voice->number;
	u32 *table_base = (u32 *)(emu->dma_buffer.area+1024*voice);
	u32 period_size_bytes = frames_to_bytes(runtime, runtime->period_size);
	int i;
	
	for(i = 0; i < runtime->periods; i++) {
		*table_base++=runtime->dma_addr+(i*period_size_bytes);
		*table_base++=period_size_bytes<<16;
	}

	snd_emu10k1x_ptr_write(emu, PLAYBACK_LIST_ADDR, voice, emu->dma_buffer.addr+1024*voice);
	snd_emu10k1x_ptr_write(emu, PLAYBACK_LIST_SIZE, voice, (runtime->periods - 1) << 19);
	snd_emu10k1x_ptr_write(emu, PLAYBACK_LIST_PTR, voice, 0);
	snd_emu10k1x_ptr_write(emu, PLAYBACK_POINTER, voice, 0);
	snd_emu10k1x_ptr_write(emu, PLAYBACK_UNKNOWN1, voice, 0);
	snd_emu10k1x_ptr_write(emu, PLAYBACK_UNKNOWN2, voice, 0);
	snd_emu10k1x_ptr_write(emu, PLAYBACK_DMA_ADDR, voice, runtime->dma_addr);

	snd_emu10k1x_ptr_write(emu, PLAYBACK_PERIOD_SIZE, voice, frames_to_bytes(runtime, runtime->period_size)<<16);

	return 0;
}