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
struct ffmpeg_source {int is_looping; int close_when_inactive; int range; int buffering_mb; int speed_percent; int is_local_file; int media_valid; void* restart_on_activate; int /*<<< orphan*/  source; int /*<<< orphan*/  media; void* seekable; void* is_clear_on_media_end; void* is_hw_decoding; int /*<<< orphan*/ * input_format; int /*<<< orphan*/ * input; } ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  enum video_range_type { ____Placeholder_video_range_type } video_range_type ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bstrdup (char*) ; 
 int /*<<< orphan*/  dump_source_info (struct ffmpeg_source*,char*,char*) ; 
 int /*<<< orphan*/  ffmpeg_source_open (struct ffmpeg_source*) ; 
 int /*<<< orphan*/  ffmpeg_source_start (struct ffmpeg_source*) ; 
 int /*<<< orphan*/  mp_media_free (int /*<<< orphan*/ *) ; 
 void* obs_data_get_bool (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int obs_source_active (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ffmpeg_source_update(void *data, obs_data_t *settings)
{
	struct ffmpeg_source *s = data;

	bool is_local_file = obs_data_get_bool(settings, "is_local_file");

	char *input;
	char *input_format;

	bfree(s->input);
	bfree(s->input_format);

	if (is_local_file) {
		input = (char *)obs_data_get_string(settings, "local_file");
		input_format = NULL;
		s->is_looping = obs_data_get_bool(settings, "looping");
		s->close_when_inactive =
			obs_data_get_bool(settings, "close_when_inactive");
	} else {
		input = (char *)obs_data_get_string(settings, "input");
		input_format =
			(char *)obs_data_get_string(settings, "input_format");
		s->is_looping = false;
		s->close_when_inactive = true;
	}

	s->input = input ? bstrdup(input) : NULL;
	s->input_format = input_format ? bstrdup(input_format) : NULL;
#ifndef __APPLE__
	s->is_hw_decoding = obs_data_get_bool(settings, "hw_decode");
#endif
	s->is_clear_on_media_end =
		obs_data_get_bool(settings, "clear_on_media_end");
	s->restart_on_activate =
		obs_data_get_bool(settings, "restart_on_activate");
	s->range = (enum video_range_type)obs_data_get_int(settings,
							   "color_range");
	s->buffering_mb = (int)obs_data_get_int(settings, "buffering_mb");
	s->speed_percent = (int)obs_data_get_int(settings, "speed_percent");
	s->is_local_file = is_local_file;
	s->seekable = obs_data_get_bool(settings, "seekable");

	if (s->speed_percent < 1 || s->speed_percent > 200)
		s->speed_percent = 100;

	if (s->media_valid) {
		mp_media_free(&s->media);
		s->media_valid = false;
	}

	bool active = obs_source_active(s->source);
	if (!s->close_when_inactive || active)
		ffmpeg_source_open(s);

	dump_source_info(s, input, input_format);
	if (!s->restart_on_activate || active)
		ffmpeg_source_start(s);
}