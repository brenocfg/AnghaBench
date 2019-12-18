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
struct mp_media_info {int buffering; int is_local_file; int /*<<< orphan*/  hardware_decoding; int /*<<< orphan*/  force_range; int /*<<< orphan*/  speed; int /*<<< orphan*/  format; scalar_t__* path; int /*<<< orphan*/  stop_cb; int /*<<< orphan*/  a_cb; int /*<<< orphan*/  v_preload_cb; int /*<<< orphan*/  v_cb; struct ffmpeg_source* opaque; } ;
struct ffmpeg_source {int buffering_mb; int /*<<< orphan*/  media; int /*<<< orphan*/  media_valid; int /*<<< orphan*/  seekable; int /*<<< orphan*/  is_local_file; int /*<<< orphan*/  is_hw_decoding; int /*<<< orphan*/  range; int /*<<< orphan*/  speed_percent; int /*<<< orphan*/  input_format; scalar_t__* input; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_audio ; 
 int /*<<< orphan*/  get_frame ; 
 int /*<<< orphan*/  media_stopped ; 
 int /*<<< orphan*/  mp_media_init (int /*<<< orphan*/ *,struct mp_media_info*) ; 
 int /*<<< orphan*/  preload_frame ; 

__attribute__((used)) static void ffmpeg_source_open(struct ffmpeg_source *s)
{
	if (s->input && *s->input) {
		struct mp_media_info info = {
			.opaque = s,
			.v_cb = get_frame,
			.v_preload_cb = preload_frame,
			.a_cb = get_audio,
			.stop_cb = media_stopped,
			.path = s->input,
			.format = s->input_format,
			.buffering = s->buffering_mb * 1024 * 1024,
			.speed = s->speed_percent,
			.force_range = s->range,
			.hardware_decoding = s->is_hw_decoding,
			.is_local_file = s->is_local_file || s->seekable};

		s->media_valid = mp_media_init(&s->media, &info);
	}
}