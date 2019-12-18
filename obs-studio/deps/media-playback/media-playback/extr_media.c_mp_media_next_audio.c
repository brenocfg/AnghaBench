#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct obs_source_audio {int samples_per_sec; scalar_t__ format; scalar_t__ timestamp; int /*<<< orphan*/  frames; int /*<<< orphan*/  speakers; int /*<<< orphan*/ * data; int /*<<< orphan*/  member_0; } ;
struct mp_decode {int frame_ready; scalar_t__ frame_pts; TYPE_2__* frame; } ;
struct TYPE_5__ {int speed; int /*<<< orphan*/  opaque; int /*<<< orphan*/  (* a_cb ) (int /*<<< orphan*/ ,struct obs_source_audio*) ;scalar_t__ play_sys_ts; scalar_t__ start_ts; scalar_t__ base_ts; struct mp_decode a; } ;
typedef  TYPE_1__ mp_media_t ;
struct TYPE_6__ {int sample_rate; int /*<<< orphan*/  nb_samples; int /*<<< orphan*/  format; int /*<<< orphan*/  channels; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 scalar_t__ AUDIO_FORMAT_UNKNOWN ; 
 size_t MAX_AV_PLANES ; 
 scalar_t__ base_sys_ts ; 
 scalar_t__ convert_sample_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_speaker_layout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_media_can_play_frame (TYPE_1__*,struct mp_decode*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct obs_source_audio*) ; 

__attribute__((used)) static void mp_media_next_audio(mp_media_t *m)
{
	struct mp_decode *d = &m->a;
	struct obs_source_audio audio = {0};
	AVFrame *f = d->frame;

	if (!mp_media_can_play_frame(m, d))
		return;

	d->frame_ready = false;
	if (!m->a_cb)
		return;

	for (size_t i = 0; i < MAX_AV_PLANES; i++)
		audio.data[i] = f->data[i];

	audio.samples_per_sec = f->sample_rate * m->speed / 100;
	audio.speakers = convert_speaker_layout(f->channels);
	audio.format = convert_sample_format(f->format);
	audio.frames = f->nb_samples;
	audio.timestamp = m->base_ts + d->frame_pts - m->start_ts +
			  m->play_sys_ts - base_sys_ts;

	if (audio.format == AUDIO_FORMAT_UNKNOWN)
		return;

	m->a_cb(m->opaque, &audio);
}