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
struct TYPE_4__ {int rates; int rate_min; } ;
struct snd_pcm_runtime {TYPE_2__ hw; } ;
struct snd_ice1712 {TYPE_1__* ac97; struct snd_pcm_substream* capture_con_substream; } ;
struct TYPE_3__ {int* rates; } ;

/* Variables and functions */
 size_t AC97_RATES_ADC ; 
 int SNDRV_PCM_RATE_8000 ; 
 TYPE_2__ snd_ice1712_capture ; 
 struct snd_ice1712* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_ice1712_capture_open(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);

	ice->capture_con_substream = substream;
	runtime->hw = snd_ice1712_capture;
	runtime->hw.rates = ice->ac97->rates[AC97_RATES_ADC];
	if (!(runtime->hw.rates & SNDRV_PCM_RATE_8000))
		runtime->hw.rate_min = 48000;
	return 0;
}