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
struct snd_msnd {void* capture_channels; void* capture_sample_rate; void* capture_sample_size; void* play_channels; void* play_sample_rate; void* play_sample_size; } ;

/* Variables and functions */
 void* DEFCHANNELS ; 
 void* DEFSAMPLERATE ; 
 int /*<<< orphan*/  DEFSAMPLESIZE ; 
 void* snd_pcm_format_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_default_audio_parameters(struct snd_msnd *chip)
{
	chip->play_sample_size = snd_pcm_format_width(DEFSAMPLESIZE);
	chip->play_sample_rate = DEFSAMPLERATE;
	chip->play_channels = DEFCHANNELS;
	chip->capture_sample_size = snd_pcm_format_width(DEFSAMPLESIZE);
	chip->capture_sample_rate = DEFSAMPLERATE;
	chip->capture_channels = DEFCHANNELS;
}