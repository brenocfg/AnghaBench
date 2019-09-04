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
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct snd_amd7930 {int flags; size_t c_cur; size_t c_orig; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int AMD7930_FLAG_CAPTURE ; 
 int /*<<< orphan*/  bytes_to_frames (int /*<<< orphan*/ ,size_t) ; 
 struct snd_amd7930* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_amd7930_capture_pointer(struct snd_pcm_substream *substream)
{
	struct snd_amd7930 *amd = snd_pcm_substream_chip(substream);
	size_t ptr;

	if (!(amd->flags & AMD7930_FLAG_CAPTURE))
		return 0;

	ptr = amd->c_cur - amd->c_orig;
	return bytes_to_frames(substream->runtime, ptr);
}