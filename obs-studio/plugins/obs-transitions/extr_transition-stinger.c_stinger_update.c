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
typedef  void* uint64_t ;
struct stinger_info {int transition_point_is_frame; int monitoring_type; int fade_style; int /*<<< orphan*/  mix_b; int /*<<< orphan*/  mix_a; int /*<<< orphan*/  media_source; void* transition_point_ns; void* transition_point_frame; } ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  long long int64_t ;
typedef  enum fade_style { ____Placeholder_fade_style } fade_style ;

/* Variables and functions */
#define  FADE_STYLE_CROSS_FADE 129 
#define  FADE_STYLE_FADE_OUT_FADE_IN 128 
 scalar_t__ TIMING_FRAME ; 
 int /*<<< orphan*/  mix_a_cross_fade ; 
 int /*<<< orphan*/  mix_a_fade_in_out ; 
 int /*<<< orphan*/  mix_b_cross_fade ; 
 int /*<<< orphan*/  mix_b_fade_in_out ; 
 int /*<<< orphan*/ * obs_data_create () ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_set_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  obs_source_create_private (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_set_monitoring_type (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stinger_update(void *data, obs_data_t *settings)
{
	struct stinger_info *s = data;
	const char *path = obs_data_get_string(settings, "path");

	obs_data_t *media_settings = obs_data_create();
	obs_data_set_string(media_settings, "local_file", path);

	obs_source_release(s->media_source);
	s->media_source = obs_source_create_private("ffmpeg_source", NULL,
						    media_settings);
	obs_data_release(media_settings);

	int64_t point = obs_data_get_int(settings, "transition_point");

	s->transition_point_is_frame = obs_data_get_int(settings, "tp_type") ==
				       TIMING_FRAME;

	if (s->transition_point_is_frame)
		s->transition_point_frame = (uint64_t)point;
	else
		s->transition_point_ns = (uint64_t)(point * 1000000LL);

	s->monitoring_type =
		(int)obs_data_get_int(settings, "audio_monitoring");
	obs_source_set_monitoring_type(s->media_source, s->monitoring_type);

	s->fade_style =
		(enum fade_style)obs_data_get_int(settings, "audio_fade_style");

	switch (s->fade_style) {
	default:
	case FADE_STYLE_FADE_OUT_FADE_IN:
		s->mix_a = mix_a_fade_in_out;
		s->mix_b = mix_b_fade_in_out;
		break;
	case FADE_STYLE_CROSS_FADE:
		s->mix_a = mix_a_cross_fade;
		s->mix_b = mix_b_cross_fade;
		break;
	}
}