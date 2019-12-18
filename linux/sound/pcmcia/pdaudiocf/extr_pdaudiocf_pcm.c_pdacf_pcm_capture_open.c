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
struct snd_pdacf {int chip_status; struct snd_pcm_substream* pcm_substream; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct snd_pdacf* private_data; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int EBUSY ; 
 int PDAUDIOCF_STAT_IS_STALE ; 
 int /*<<< orphan*/  pdacf_pcm_capture_hw ; 
 struct snd_pdacf* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int pdacf_pcm_capture_open(struct snd_pcm_substream *subs)
{
	struct snd_pcm_runtime *runtime = subs->runtime;
	struct snd_pdacf *chip = snd_pcm_substream_chip(subs);

	if (chip->chip_status & PDAUDIOCF_STAT_IS_STALE)
		return -EBUSY;

	runtime->hw = pdacf_pcm_capture_hw;
	runtime->private_data = chip;
	chip->pcm_substream = subs;

	return 0;
}