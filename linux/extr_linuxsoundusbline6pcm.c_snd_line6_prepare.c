#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {int /*<<< orphan*/  stream; } ;
struct TYPE_4__ {scalar_t__ bytes; scalar_t__ pos_done; scalar_t__ count; } ;
struct TYPE_3__ {scalar_t__ bytes; scalar_t__ pos_done; scalar_t__ pos; scalar_t__ count; } ;
struct snd_line6_pcm {int /*<<< orphan*/  state_mutex; TYPE_2__ in; TYPE_1__ out; int /*<<< orphan*/  flags; } ;
struct line6_pcm_stream {int /*<<< orphan*/  running; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE6_FLAG_PREPARED ; 
 struct line6_pcm_stream* get_stream (struct snd_line6_pcm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line6_wait_clear_audio_urbs (struct snd_line6_pcm*,struct line6_pcm_stream*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_line6_pcm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int snd_line6_prepare(struct snd_pcm_substream *substream)
{
	struct snd_line6_pcm *line6pcm = snd_pcm_substream_chip(substream);
	struct line6_pcm_stream *pstr = get_stream(line6pcm, substream->stream);

	mutex_lock(&line6pcm->state_mutex);
	if (!pstr->running)
		line6_wait_clear_audio_urbs(line6pcm, pstr);

	if (!test_and_set_bit(LINE6_FLAG_PREPARED, &line6pcm->flags)) {
		line6pcm->out.count = 0;
		line6pcm->out.pos = 0;
		line6pcm->out.pos_done = 0;
		line6pcm->out.bytes = 0;
		line6pcm->in.count = 0;
		line6pcm->in.pos_done = 0;
		line6pcm->in.bytes = 0;
	}

	mutex_unlock(&line6pcm->state_mutex);
	return 0;
}