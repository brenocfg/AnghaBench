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
typedef  int u32 ;
struct snd_pcm_substream {TYPE_1__* pcm; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int period_size; int rate; int periods; int dma_addr; scalar_t__ dma_area; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  channels; int /*<<< orphan*/  format; } ;
struct TYPE_6__ {int addr; int* bytes; scalar_t__ area; } ;
struct snd_emu10k1 {int p16v_device_offset; TYPE_3__ p16v_buffer; TYPE_2__* card; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int device; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SPDIF_SAMPLERATE ; 
 int PLAYBACK_DMA_ADDR ; 
 int PLAYBACK_LIST_ADDR ; 
 int PLAYBACK_LIST_PTR ; 
 int PLAYBACK_LIST_SIZE ; 
 int PLAYBACK_PERIOD_SIZE ; 
 int PLAYBACK_POINTER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int*,...) ; 
 int frames_to_bytes (struct snd_pcm_runtime*,int) ; 
 int /*<<< orphan*/  snd_emu10k1_ptr20_write (struct snd_emu10k1*,int,int,int) ; 
 int snd_emu10k1_ptr_read (struct snd_emu10k1*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,int /*<<< orphan*/ ,int,int) ; 
 struct snd_emu10k1* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_p16v_pcm_prepare_playback(struct snd_pcm_substream *substream)
{
	struct snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	int channel = substream->pcm->device - emu->p16v_device_offset;
	u32 *table_base = (u32 *)(emu->p16v_buffer.area+(8*16*channel));
	u32 period_size_bytes = frames_to_bytes(runtime, runtime->period_size);
	int i;
	u32 tmp;
	
#if 0 /* debug */
	dev_dbg(emu->card->dev,
		"prepare:channel_number=%d, rate=%d, "
		   "format=0x%x, channels=%d, buffer_size=%ld, "
		   "period_size=%ld, periods=%u, frames_to_bytes=%d\n",
		   channel, runtime->rate, runtime->format, runtime->channels,
		   runtime->buffer_size, runtime->period_size,
		   runtime->periods, frames_to_bytes(runtime, 1));
	dev_dbg(emu->card->dev,
		"dma_addr=%x, dma_area=%p, table_base=%p\n",
		   runtime->dma_addr, runtime->dma_area, table_base);
	dev_dbg(emu->card->dev,
		"dma_addr=%x, dma_area=%p, dma_bytes(size)=%x\n",
		   emu->p16v_buffer.addr, emu->p16v_buffer.area,
		   emu->p16v_buffer.bytes);
#endif /* debug */
	tmp = snd_emu10k1_ptr_read(emu, A_SPDIF_SAMPLERATE, channel);
        switch (runtime->rate) {
	case 44100:
	  snd_emu10k1_ptr_write(emu, A_SPDIF_SAMPLERATE, channel, (tmp & ~0xe0e0) | 0x8080);
	  break;
	case 96000:
	  snd_emu10k1_ptr_write(emu, A_SPDIF_SAMPLERATE, channel, (tmp & ~0xe0e0) | 0x4040);
	  break;
	case 192000:
	  snd_emu10k1_ptr_write(emu, A_SPDIF_SAMPLERATE, channel, (tmp & ~0xe0e0) | 0x2020);
	  break;
	case 48000:
	default:
	  snd_emu10k1_ptr_write(emu, A_SPDIF_SAMPLERATE, channel, (tmp & ~0xe0e0) | 0x0000);
	  break;
	}
	/* FIXME: Check emu->buffer.size before actually writing to it. */
	for(i = 0; i < runtime->periods; i++) {
		table_base[i*2]=runtime->dma_addr+(i*period_size_bytes);
		table_base[(i*2)+1]=period_size_bytes<<16;
	}
 
	snd_emu10k1_ptr20_write(emu, PLAYBACK_LIST_ADDR, channel, emu->p16v_buffer.addr+(8*16*channel));
	snd_emu10k1_ptr20_write(emu, PLAYBACK_LIST_SIZE, channel, (runtime->periods - 1) << 19);
	snd_emu10k1_ptr20_write(emu, PLAYBACK_LIST_PTR, channel, 0);
	snd_emu10k1_ptr20_write(emu, PLAYBACK_DMA_ADDR, channel, runtime->dma_addr);
	//snd_emu10k1_ptr20_write(emu, PLAYBACK_PERIOD_SIZE, channel, frames_to_bytes(runtime, runtime->period_size)<<16); // buffer size in bytes
	snd_emu10k1_ptr20_write(emu, PLAYBACK_PERIOD_SIZE, channel, 0); // buffer size in bytes
	snd_emu10k1_ptr20_write(emu, PLAYBACK_POINTER, channel, 0);
	snd_emu10k1_ptr20_write(emu, 0x07, channel, 0x0);
	snd_emu10k1_ptr20_write(emu, 0x08, channel, 0);

	return 0;
}