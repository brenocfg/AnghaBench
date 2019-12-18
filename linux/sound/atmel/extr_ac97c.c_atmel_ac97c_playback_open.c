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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct TYPE_2__ {int /*<<< orphan*/  formats; scalar_t__ rate_max; scalar_t__ rate_min; } ;
struct snd_pcm_runtime {TYPE_1__ hw; } ;
struct atmel_ac97c {struct snd_pcm_substream* playback_substream; scalar_t__ cur_format; scalar_t__ cur_rate; int /*<<< orphan*/  opened; } ;

/* Variables and functions */
 TYPE_1__ atmel_ac97c_hw ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opened_mutex ; 
 int /*<<< orphan*/  pcm_format_to_bits (scalar_t__) ; 
 struct atmel_ac97c* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int atmel_ac97c_playback_open(struct snd_pcm_substream *substream)
{
	struct atmel_ac97c *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;

	mutex_lock(&opened_mutex);
	chip->opened++;
	runtime->hw = atmel_ac97c_hw;
	if (chip->cur_rate) {
		runtime->hw.rate_min = chip->cur_rate;
		runtime->hw.rate_max = chip->cur_rate;
	}
	if (chip->cur_format)
		runtime->hw.formats = pcm_format_to_bits(chip->cur_format);
	mutex_unlock(&opened_mutex);
	chip->playback_substream = substream;
	return 0;
}