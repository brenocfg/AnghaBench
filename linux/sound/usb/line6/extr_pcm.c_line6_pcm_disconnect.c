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
struct snd_line6_pcm {int /*<<< orphan*/  in; int /*<<< orphan*/  out; } ;

/* Variables and functions */
 int /*<<< orphan*/  line6_unlink_audio_urbs (struct snd_line6_pcm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  line6_wait_clear_audio_urbs (struct snd_line6_pcm*,int /*<<< orphan*/ *) ; 

void line6_pcm_disconnect(struct snd_line6_pcm *line6pcm)
{
	line6_unlink_audio_urbs(line6pcm, &line6pcm->out);
	line6_unlink_audio_urbs(line6pcm, &line6pcm->in);
	line6_wait_clear_audio_urbs(line6pcm, &line6pcm->out);
	line6_wait_clear_audio_urbs(line6pcm, &line6pcm->in);
}