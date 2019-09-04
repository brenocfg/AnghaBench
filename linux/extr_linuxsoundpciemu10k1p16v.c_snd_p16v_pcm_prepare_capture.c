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
typedef  int u32 ;
struct snd_pcm_substream {TYPE_1__* pcm; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int rate; int dma_addr; int /*<<< orphan*/  buffer_size; } ;
struct snd_emu10k1 {int p16v_device_offset; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SPDIF_SAMPLERATE ; 
 int CAPTURE_BUFFER_SIZE ; 
 int CAPTURE_DMA_ADDR ; 
 int CAPTURE_POINTER ; 
 int frames_to_bytes (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1_ptr20_write (struct snd_emu10k1*,int,int,int) ; 
 int snd_emu10k1_ptr_read (struct snd_emu10k1*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,int /*<<< orphan*/ ,int,int) ; 
 struct snd_emu10k1* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_p16v_pcm_prepare_capture(struct snd_pcm_substream *substream)
{
	struct snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	int channel = substream->pcm->device - emu->p16v_device_offset;
	u32 tmp;

	/*
	dev_dbg(emu->card->dev, "prepare capture:channel_number=%d, rate=%d, "
	       "format=0x%x, channels=%d, buffer_size=%ld, period_size=%ld, "
	       "frames_to_bytes=%d\n",
	       channel, runtime->rate, runtime->format, runtime->channels,
	       runtime->buffer_size, runtime->period_size,
	       frames_to_bytes(runtime, 1));
	*/
	tmp = snd_emu10k1_ptr_read(emu, A_SPDIF_SAMPLERATE, channel);
        switch (runtime->rate) {
	case 44100:
	  snd_emu10k1_ptr_write(emu, A_SPDIF_SAMPLERATE, channel, (tmp & ~0x0e00) | 0x0800);
	  break;
	case 96000:
	  snd_emu10k1_ptr_write(emu, A_SPDIF_SAMPLERATE, channel, (tmp & ~0x0e00) | 0x0400);
	  break;
	case 192000:
	  snd_emu10k1_ptr_write(emu, A_SPDIF_SAMPLERATE, channel, (tmp & ~0x0e00) | 0x0200);
	  break;
	case 48000:
	default:
	  snd_emu10k1_ptr_write(emu, A_SPDIF_SAMPLERATE, channel, (tmp & ~0x0e00) | 0x0000);
	  break;
	}
	/* FIXME: Check emu->buffer.size before actually writing to it. */
	snd_emu10k1_ptr20_write(emu, 0x13, channel, 0);
	snd_emu10k1_ptr20_write(emu, CAPTURE_DMA_ADDR, channel, runtime->dma_addr);
	snd_emu10k1_ptr20_write(emu, CAPTURE_BUFFER_SIZE, channel, frames_to_bytes(runtime, runtime->buffer_size) << 16); // buffer size in bytes
	snd_emu10k1_ptr20_write(emu, CAPTURE_POINTER, channel, 0);
	//snd_emu10k1_ptr20_write(emu, CAPTURE_SOURCE, 0x0, 0x333300e4); /* Select MIC or Line in */
	//snd_emu10k1_ptr20_write(emu, EXTENDED_INT_MASK, 0, snd_emu10k1_ptr20_read(emu, EXTENDED_INT_MASK, 0) | (0x110000<<channel));

	return 0;
}