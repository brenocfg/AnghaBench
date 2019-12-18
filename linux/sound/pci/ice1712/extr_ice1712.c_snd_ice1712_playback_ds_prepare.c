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
typedef  int u32 ;
struct snd_pcm_substream {size_t number; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; int rate; int dma_addr; int periods; int /*<<< orphan*/  format; } ;
struct snd_ice1712 {int* playback_con_virt_addr; int /*<<< orphan*/  reg_lock; scalar_t__* playback_con_active_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE1712_DSC_ADDR0 ; 
 int /*<<< orphan*/  ICE1712_DSC_ADDR1 ; 
 int /*<<< orphan*/  ICE1712_DSC_CONTROL ; 
 int /*<<< orphan*/  ICE1712_DSC_COUNT0 ; 
 int /*<<< orphan*/  ICE1712_DSC_COUNT1 ; 
 int /*<<< orphan*/  ICE1712_DSC_RATE ; 
 int /*<<< orphan*/  ICE1712_DSC_VOLUME ; 
 int /*<<< orphan*/  snd_ice1712_ds_write (struct snd_ice1712*,int,int /*<<< orphan*/ ,int) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct snd_ice1712* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ice1712_playback_ds_prepare(struct snd_pcm_substream *substream)
{
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	u32 period_size, rate, tmp, chn;

	period_size = snd_pcm_lib_period_bytes(substream) - 1;
	tmp = 0x0064;
	if (snd_pcm_format_width(runtime->format) == 16)
		tmp &= ~0x04;
	if (runtime->channels == 2)
		tmp |= 0x08;
	rate = (runtime->rate * 8192) / 375;
	if (rate > 0x000fffff)
		rate = 0x000fffff;
	ice->playback_con_active_buf[substream->number] = 0;
	ice->playback_con_virt_addr[substream->number] = runtime->dma_addr;
	chn = substream->number * 2;
	spin_lock_irq(&ice->reg_lock);
	snd_ice1712_ds_write(ice, chn, ICE1712_DSC_ADDR0, runtime->dma_addr);
	snd_ice1712_ds_write(ice, chn, ICE1712_DSC_COUNT0, period_size);
	snd_ice1712_ds_write(ice, chn, ICE1712_DSC_ADDR1, runtime->dma_addr + (runtime->periods > 1 ? period_size + 1 : 0));
	snd_ice1712_ds_write(ice, chn, ICE1712_DSC_COUNT1, period_size);
	snd_ice1712_ds_write(ice, chn, ICE1712_DSC_RATE, rate);
	snd_ice1712_ds_write(ice, chn, ICE1712_DSC_VOLUME, 0);
	snd_ice1712_ds_write(ice, chn, ICE1712_DSC_CONTROL, tmp);
	if (runtime->channels == 2) {
		snd_ice1712_ds_write(ice, chn + 1, ICE1712_DSC_RATE, rate);
		snd_ice1712_ds_write(ice, chn + 1, ICE1712_DSC_VOLUME, 0);
	}
	spin_unlock_irq(&ice->reg_lock);
	return 0;
}