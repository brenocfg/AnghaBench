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
struct snd_line6_pcm {int /*<<< orphan*/  state_mutex; } ;
struct line6_pcm_stream {int /*<<< orphan*/  running; } ;

/* Variables and functions */
 struct line6_pcm_stream* get_stream (struct snd_line6_pcm*,int) ; 
 int line6_buffer_acquire (struct snd_line6_pcm*,struct line6_pcm_stream*,int,int) ; 
 int /*<<< orphan*/  line6_pcm_release (struct snd_line6_pcm*,int) ; 
 int line6_stream_start (struct snd_line6_pcm*,int,int) ; 
 int /*<<< orphan*/  line6_wait_clear_audio_urbs (struct snd_line6_pcm*,struct line6_pcm_stream*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int line6_pcm_acquire(struct snd_line6_pcm *line6pcm, int type, bool start)
{
	struct line6_pcm_stream *pstr;
	int ret = 0, dir;

	/* TODO: We should assert SNDRV_PCM_STREAM_PLAYBACK/CAPTURE == 0/1 */
	mutex_lock(&line6pcm->state_mutex);
	for (dir = 0; dir < 2; dir++) {
		pstr = get_stream(line6pcm, dir);
		ret = line6_buffer_acquire(line6pcm, pstr, dir, type);
		if (ret < 0)
			goto error;
		if (!pstr->running)
			line6_wait_clear_audio_urbs(line6pcm, pstr);
	}
	if (start) {
		for (dir = 0; dir < 2; dir++) {
			ret = line6_stream_start(line6pcm, dir, type);
			if (ret < 0)
				goto error;
		}
	}
 error:
	mutex_unlock(&line6pcm->state_mutex);
	if (ret < 0)
		line6_pcm_release(line6pcm, type);
	return ret;
}