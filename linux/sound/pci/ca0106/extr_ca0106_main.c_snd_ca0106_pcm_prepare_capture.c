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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int rate; int format; int buffer_size; int dma_addr; int /*<<< orphan*/  dma_area; int /*<<< orphan*/  periods; int /*<<< orphan*/  period_size; int /*<<< orphan*/  channels; struct snd_ca0106_pcm* private_data; } ;
struct snd_ca0106_pcm {int channel_id; } ;
struct TYPE_5__ {int addr; int /*<<< orphan*/  bytes; int /*<<< orphan*/  area; } ;
struct snd_ca0106 {TYPE_3__* details; scalar_t__ port; TYPE_2__ buffer; TYPE_1__* card; } ;
struct TYPE_6__ {int i2c_adc; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_MASTER ; 
 int CAPTURE_BUFFER_SIZE ; 
 int CAPTURE_DMA_ADDR ; 
 int CAPTURE_POINTER ; 
 scalar_t__ HCFG ; 
 int HCFG_CAPTURE_S32_LE ; 
#define  SNDRV_PCM_FORMAT_S16_LE 129 
#define  SNDRV_PCM_FORMAT_S32_LE 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int,...) ; 
 int frames_to_bytes (struct snd_pcm_runtime*,int) ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  snd_ca0106_i2c_write (struct snd_ca0106*,int /*<<< orphan*/ ,int) ; 
 int snd_ca0106_ptr_read (struct snd_ca0106*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ca0106_ptr_write (struct snd_ca0106*,int,int,int) ; 
 struct snd_ca0106* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  table_base ; 

__attribute__((used)) static int snd_ca0106_pcm_prepare_capture(struct snd_pcm_substream *substream)
{
	struct snd_ca0106 *emu = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_ca0106_pcm *epcm = runtime->private_data;
	int channel = epcm->channel_id;
	u32 hcfg_mask = HCFG_CAPTURE_S32_LE;
	u32 hcfg_set = 0x00000000;
	u32 hcfg;
	u32 over_sampling=0x2;
	u32 reg71_mask = 0x0000c000 ; /* Global. Set ADC rate. */
	u32 reg71_set = 0;
	u32 reg71;
	
#if 0 /* debug */
	dev_dbg(emu->card->dev,
		   "prepare:channel_number=%d, rate=%d, format=0x%x, "
		   "channels=%d, buffer_size=%ld, period_size=%ld, "
		   "periods=%u, frames_to_bytes=%d\n",
		   channel, runtime->rate, runtime->format,
		   runtime->channels, runtime->buffer_size,
		   runtime->period_size, runtime->periods,
		   frames_to_bytes(runtime, 1));
	dev_dbg(emu->card->dev,
		"dma_addr=%x, dma_area=%p, table_base=%p\n",
		   runtime->dma_addr, runtime->dma_area, table_base);
	dev_dbg(emu->card->dev,
		"dma_addr=%x, dma_area=%p, dma_bytes(size)=%x\n",
		   emu->buffer.addr, emu->buffer.area, emu->buffer.bytes);
#endif /* debug */
	/* reg71 controls ADC rate. */
	switch (runtime->rate) {
	case 44100:
		reg71_set = 0x00004000;
		break;
        case 48000:
		reg71_set = 0; 
		break;
	case 96000:
		reg71_set = 0x00008000;
		over_sampling=0xa;
		break;
	case 192000:
		reg71_set = 0x0000c000; 
		over_sampling=0xa;
		break;
	default:
		reg71_set = 0; 
		break;
	}
	/* Format is a global setting */
	/* FIXME: Only let the first channel accessed set this. */
	switch (runtime->format) {
	case SNDRV_PCM_FORMAT_S16_LE:
		hcfg_set = 0;
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		hcfg_set = HCFG_CAPTURE_S32_LE;
		break;
	default:
		hcfg_set = 0;
		break;
	}
	hcfg = inl(emu->port + HCFG) ;
	hcfg = (hcfg & ~hcfg_mask) | hcfg_set;
	outl(hcfg, emu->port + HCFG);
	reg71 = snd_ca0106_ptr_read(emu, 0x71, 0);
	reg71 = (reg71 & ~reg71_mask) | reg71_set;
	snd_ca0106_ptr_write(emu, 0x71, 0, reg71);
        if (emu->details->i2c_adc == 1) { /* The SB0410 and SB0413 use I2C to control ADC. */
	        snd_ca0106_i2c_write(emu, ADC_MASTER, over_sampling); /* Adjust the over sampler to better suit the capture rate. */
	}


	/*
	dev_dbg(emu->card->dev,
	       "prepare:channel_number=%d, rate=%d, format=0x%x, channels=%d, "
	       "buffer_size=%ld, period_size=%ld, frames_to_bytes=%d\n",
	       channel, runtime->rate, runtime->format, runtime->channels,
	       runtime->buffer_size, runtime->period_size,
	       frames_to_bytes(runtime, 1));
	*/
	snd_ca0106_ptr_write(emu, 0x13, channel, 0);
	snd_ca0106_ptr_write(emu, CAPTURE_DMA_ADDR, channel, runtime->dma_addr);
	snd_ca0106_ptr_write(emu, CAPTURE_BUFFER_SIZE, channel, frames_to_bytes(runtime, runtime->buffer_size)<<16); // buffer size in bytes
	snd_ca0106_ptr_write(emu, CAPTURE_POINTER, channel, 0);

	return 0;
}