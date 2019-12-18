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
struct line6_pcm_stream {int dummy; } ;

/* Variables and functions */
 struct line6_pcm_stream* get_stream (struct snd_line6_pcm*,int) ; 
 int /*<<< orphan*/  line6_buffer_release (struct snd_line6_pcm*,struct line6_pcm_stream*,int) ; 
 int /*<<< orphan*/  line6_stream_stop (struct snd_line6_pcm*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void line6_pcm_release(struct snd_line6_pcm *line6pcm, int type)
{
	struct line6_pcm_stream *pstr;
	int dir;

	mutex_lock(&line6pcm->state_mutex);
	for (dir = 0; dir < 2; dir++)
		line6_stream_stop(line6pcm, dir, type);
	for (dir = 0; dir < 2; dir++) {
		pstr = get_stream(line6pcm, dir);
		line6_buffer_release(line6pcm, pstr, type);
	}
	mutex_unlock(&line6pcm->state_mutex);
}