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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_format_unsigned (int /*<<< orphan*/ ) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int snd_ali_control_mode(struct snd_pcm_substream *substream)
{
	unsigned int CTRL;
	struct snd_pcm_runtime *runtime = substream->runtime;

	/* set ctrl mode
	   CTRL default: 8-bit (unsigned) mono, loop mode enabled
	 */
	CTRL = 0x00000001;
	if (snd_pcm_format_width(runtime->format) == 16)
		CTRL |= 0x00000008;	/* 16-bit data */
	if (!snd_pcm_format_unsigned(runtime->format))
		CTRL |= 0x00000002;	/* signed data */
	if (runtime->channels > 1)
		CTRL |= 0x00000004;	/* stereo data */
	return CTRL;
}