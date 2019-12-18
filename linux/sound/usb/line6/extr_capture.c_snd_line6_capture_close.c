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
struct snd_line6_pcm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE6_STREAM_CAPTURE_HELPER ; 
 int /*<<< orphan*/  line6_pcm_release (struct snd_line6_pcm*,int /*<<< orphan*/ ) ; 
 struct snd_line6_pcm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_line6_capture_close(struct snd_pcm_substream *substream)
{
	struct snd_line6_pcm *line6pcm = snd_pcm_substream_chip(substream);

	line6_pcm_release(line6pcm, LINE6_STREAM_CAPTURE_HELPER);
	return 0;
}