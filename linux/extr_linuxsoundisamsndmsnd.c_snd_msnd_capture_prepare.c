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
struct snd_pcm_substream {int dummy; } ;
struct snd_msnd {scalar_t__ captureDMAPos; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_msnd_capture_reset_queue (struct snd_msnd*,unsigned int,unsigned int) ; 
 unsigned int snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 unsigned int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct snd_msnd* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_msnd_capture_prepare(struct snd_pcm_substream *substream)
{
	struct snd_msnd *chip = snd_pcm_substream_chip(substream);
	unsigned int pcm_size = snd_pcm_lib_buffer_bytes(substream);
	unsigned int pcm_count = snd_pcm_lib_period_bytes(substream);
	unsigned int pcm_periods = pcm_size / pcm_count;

	snd_msnd_capture_reset_queue(chip, pcm_periods, pcm_count);
	chip->captureDMAPos = 0;
	return 0;
}