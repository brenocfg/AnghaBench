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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; int dma_addr; int /*<<< orphan*/  rate; int /*<<< orphan*/  format; } ;
struct TYPE_3__ {int pclkdiv_lock; } ;
struct TYPE_4__ {TYPE_1__ es1370; } ;
struct ensoniq {int c_dma_size; int c_period_size; int ctrl; int sctrl; int /*<<< orphan*/  reg_lock; TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_COUNT ; 
 int /*<<< orphan*/  ADC_FRAME ; 
 int /*<<< orphan*/  ADC_SIZE ; 
 int /*<<< orphan*/  CONTROL ; 
 int ES_1370_PCLKDIVM ; 
 int ES_1370_PCLKDIVO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ES_1370_SRTODIV (int /*<<< orphan*/ ) ; 
 int ES_ADC_EN ; 
 int ES_MEM_PAGEO (int /*<<< orphan*/ ) ; 
 int ES_MODE_CAPTURE ; 
 int ES_MODE_PLAY2 ; 
 int /*<<< orphan*/  ES_PAGE_ADC ; 
 int ES_R1_INT_EN ; 
 int ES_R1_LOOP_SEL ; 
 int ES_R1_MODEM ; 
 int ES_R1_MODEO (unsigned int) ; 
 int /*<<< orphan*/  ES_REG (struct ensoniq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_PAGE ; 
 int /*<<< orphan*/  SERIAL ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 
 int* snd_ensoniq_sample_shift ; 
 int /*<<< orphan*/  snd_es1371_adc_rate (struct ensoniq*,int /*<<< orphan*/ ) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 int snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct ensoniq* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ensoniq_capture_prepare(struct snd_pcm_substream *substream)
{
	struct ensoniq *ensoniq = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned int mode = 0;

	ensoniq->c_dma_size = snd_pcm_lib_buffer_bytes(substream);
	ensoniq->c_period_size = snd_pcm_lib_period_bytes(substream);
	if (snd_pcm_format_width(runtime->format) == 16)
		mode |= 0x02;
	if (runtime->channels > 1)
		mode |= 0x01;
	spin_lock_irq(&ensoniq->reg_lock);
	ensoniq->ctrl &= ~ES_ADC_EN;
	outl(ensoniq->ctrl, ES_REG(ensoniq, CONTROL));
	outl(ES_MEM_PAGEO(ES_PAGE_ADC), ES_REG(ensoniq, MEM_PAGE));
	outl(runtime->dma_addr, ES_REG(ensoniq, ADC_FRAME));
	outl((ensoniq->c_dma_size >> 2) - 1, ES_REG(ensoniq, ADC_SIZE));
	ensoniq->sctrl &= ~(ES_R1_LOOP_SEL | ES_R1_MODEM);
	ensoniq->sctrl |= ES_R1_INT_EN | ES_R1_MODEO(mode);
	outl(ensoniq->sctrl, ES_REG(ensoniq, SERIAL));
	outl((ensoniq->c_period_size >> snd_ensoniq_sample_shift[mode]) - 1,
	     ES_REG(ensoniq, ADC_COUNT));
#ifdef CHIP1370
	if (!(ensoniq->u.es1370.pclkdiv_lock & ES_MODE_PLAY2)) {
		ensoniq->ctrl &= ~ES_1370_PCLKDIVM;
		ensoniq->ctrl |= ES_1370_PCLKDIVO(ES_1370_SRTODIV(runtime->rate));
		ensoniq->u.es1370.pclkdiv_lock |= ES_MODE_CAPTURE;
	}
#endif
	outl(ensoniq->ctrl, ES_REG(ensoniq, CONTROL));
	spin_unlock_irq(&ensoniq->reg_lock);
#ifndef CHIP1370
	snd_es1371_adc_rate(ensoniq, runtime->rate);
#endif
	return 0;
}