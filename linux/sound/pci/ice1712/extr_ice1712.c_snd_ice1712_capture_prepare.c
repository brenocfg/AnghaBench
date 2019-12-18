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
typedef  int u8 ;
typedef  int u32 ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; int /*<<< orphan*/  rate; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  format; } ;
struct snd_ice1712 {int /*<<< orphan*/  ac97; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  capture_con_virt_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_PCM_LR_ADC_RATE ; 
 int /*<<< orphan*/  CONCAP_ADDR ; 
 int /*<<< orphan*/  CONCAP_COUNT ; 
 int /*<<< orphan*/  ICE1712_IREG_CAP_COUNT_HI ; 
 int /*<<< orphan*/  ICE1712_IREG_CAP_COUNT_LO ; 
 int /*<<< orphan*/  ICE1712_IREG_CAP_CTRL ; 
 int /*<<< orphan*/  ICEREG (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ice1712_write (struct snd_ice1712*,int /*<<< orphan*/ ,int) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 int snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct snd_ice1712* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ice1712_capture_prepare(struct snd_pcm_substream *substream)
{
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	u32 period_size, buf_size;
	u8 tmp;

	period_size = (snd_pcm_lib_period_bytes(substream) >> 2) - 1;
	buf_size = snd_pcm_lib_buffer_bytes(substream) - 1;
	tmp = 0x06;
	if (snd_pcm_format_width(runtime->format) == 16)
		tmp &= ~0x04;
	if (runtime->channels == 2)
		tmp &= ~0x02;
	spin_lock_irq(&ice->reg_lock);
	outl(ice->capture_con_virt_addr = runtime->dma_addr, ICEREG(ice, CONCAP_ADDR));
	outw(buf_size, ICEREG(ice, CONCAP_COUNT));
	snd_ice1712_write(ice, ICE1712_IREG_CAP_COUNT_HI, period_size >> 8);
	snd_ice1712_write(ice, ICE1712_IREG_CAP_COUNT_LO, period_size & 0xff);
	snd_ice1712_write(ice, ICE1712_IREG_CAP_CTRL, tmp);
	spin_unlock_irq(&ice->reg_lock);
	snd_ac97_set_rate(ice->ac97, AC97_PCM_LR_ADC_RATE, runtime->rate);
	return 0;
}