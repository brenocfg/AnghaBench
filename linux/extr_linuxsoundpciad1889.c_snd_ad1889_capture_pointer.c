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
struct TYPE_2__ {int reg; size_t size; scalar_t__ addr; } ;
struct snd_ad1889 {TYPE_1__ ramc; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  AD_DMA_ADCCA ; 
 int AD_DS_RAMC_ADEN ; 
 size_t ad1889_readl (struct snd_ad1889*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytes_to_frames (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 struct snd_ad1889* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static snd_pcm_uframes_t
snd_ad1889_capture_pointer(struct snd_pcm_substream *ss)
{
	size_t ptr = 0;
	struct snd_ad1889 *chip = snd_pcm_substream_chip(ss);

	if (unlikely(!(chip->ramc.reg & AD_DS_RAMC_ADEN)))
		return 0;

	ptr = ad1889_readl(chip, AD_DMA_ADCCA);
	ptr -= chip->ramc.addr;

	if (snd_BUG_ON(ptr >= chip->ramc.size))
		return 0;
	
	return bytes_to_frames(ss->runtime, ptr);
}