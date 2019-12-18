#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_t ;
struct video_output_info {scalar_t__ range; scalar_t__ colorspace; int /*<<< orphan*/  format; } ;
struct TYPE_4__ {int /*<<< orphan*/  audio_format; scalar_t__ last_error; } ;
struct ffmpeg_output {int active; int write_thread_active; int /*<<< orphan*/  output; TYPE_1__ ff_data; int /*<<< orphan*/  write_thread; } ;
struct ffmpeg_cfg {int video_bitrate; int audio_bitrate; int gop_size; int video_encoder_id; int audio_encoder_id; int scale_width; int scale_height; int width; int height; scalar_t__ format; int audio_tracks; int /*<<< orphan*/  color_space; int /*<<< orphan*/  color_range; int /*<<< orphan*/  audio_mix_count; void* audio_settings; void* video_settings; void* audio_encoder; void* video_encoder; void* muxer_settings; void* format_mime_type; void* format_name; void* url; } ;
struct audio_convert_info {int /*<<< orphan*/  format; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVCOL_RANGE_JPEG ; 
 int /*<<< orphan*/  AVCOL_RANGE_MPEG ; 
 int /*<<< orphan*/  AVCOL_RANGE_UNSPECIFIED ; 
 int /*<<< orphan*/  AVCOL_SPC_BT470BG ; 
 int /*<<< orphan*/  AVCOL_SPC_BT709 ; 
 int /*<<< orphan*/  AVCOL_SPC_RGB ; 
 scalar_t__ AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ VIDEO_CS_709 ; 
 scalar_t__ VIDEO_RANGE_FULL ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ffmpeg_data_free (TYPE_1__*) ; 
 int ffmpeg_data_init (TYPE_1__*,struct ffmpeg_cfg*) ; 
 int /*<<< orphan*/  ffmpeg_log_error (int /*<<< orphan*/ ,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ffmpeg_output_full_stop (struct ffmpeg_output*) ; 
 scalar_t__ format_is_yuv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_audio_mix_count (int) ; 
 void* get_string_or_null (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 void* obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_set_default_int (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  obs_output_begin_data_capture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_output_can_begin_data_capture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ obs_output_get_height (int /*<<< orphan*/ ) ; 
 scalar_t__ obs_output_get_mixers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_output_get_settings (int /*<<< orphan*/ ) ; 
 scalar_t__ obs_output_get_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_output_set_audio_conversion (int /*<<< orphan*/ ,struct audio_convert_info*) ; 
 int /*<<< orphan*/  obs_output_set_last_error (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  obs_output_set_video_conversion (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_output_video (int /*<<< orphan*/ ) ; 
 scalar_t__ obs_to_ffmpeg_video_format (int /*<<< orphan*/ ) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ffmpeg_output*) ; 
 int /*<<< orphan*/  video_output_get_format (int /*<<< orphan*/ *) ; 
 struct video_output_info* video_output_get_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_thread ; 

__attribute__((used)) static bool try_connect(struct ffmpeg_output *output)
{
	video_t *video = obs_output_video(output->output);
	const struct video_output_info *voi = video_output_get_info(video);
	struct ffmpeg_cfg config;
	obs_data_t *settings;
	bool success;
	int ret;

	settings = obs_output_get_settings(output->output);

	obs_data_set_default_int(settings, "gop_size", 120);

	config.url = obs_data_get_string(settings, "url");
	config.format_name = get_string_or_null(settings, "format_name");
	config.format_mime_type =
		get_string_or_null(settings, "format_mime_type");
	config.muxer_settings = obs_data_get_string(settings, "muxer_settings");
	config.video_bitrate = (int)obs_data_get_int(settings, "video_bitrate");
	config.audio_bitrate = (int)obs_data_get_int(settings, "audio_bitrate");
	config.gop_size = (int)obs_data_get_int(settings, "gop_size");
	config.video_encoder = get_string_or_null(settings, "video_encoder");
	config.video_encoder_id =
		(int)obs_data_get_int(settings, "video_encoder_id");
	config.audio_encoder = get_string_or_null(settings, "audio_encoder");
	config.audio_encoder_id =
		(int)obs_data_get_int(settings, "audio_encoder_id");
	config.video_settings = obs_data_get_string(settings, "video_settings");
	config.audio_settings = obs_data_get_string(settings, "audio_settings");
	config.scale_width = (int)obs_data_get_int(settings, "scale_width");
	config.scale_height = (int)obs_data_get_int(settings, "scale_height");
	config.width = (int)obs_output_get_width(output->output);
	config.height = (int)obs_output_get_height(output->output);
	config.format =
		obs_to_ffmpeg_video_format(video_output_get_format(video));
	config.audio_tracks = (int)obs_output_get_mixers(output->output);
	config.audio_mix_count = get_audio_mix_count(config.audio_tracks);

	if (format_is_yuv(voi->format)) {
		config.color_range = voi->range == VIDEO_RANGE_FULL
					     ? AVCOL_RANGE_JPEG
					     : AVCOL_RANGE_MPEG;
		config.color_space = voi->colorspace == VIDEO_CS_709
					     ? AVCOL_SPC_BT709
					     : AVCOL_SPC_BT470BG;
	} else {
		config.color_range = AVCOL_RANGE_UNSPECIFIED;
		config.color_space = AVCOL_SPC_RGB;
	}

	if (config.format == AV_PIX_FMT_NONE) {
		blog(LOG_DEBUG, "invalid pixel format used for FFmpeg output");
		return false;
	}

	if (!config.scale_width)
		config.scale_width = config.width;
	if (!config.scale_height)
		config.scale_height = config.height;

	success = ffmpeg_data_init(&output->ff_data, &config);
	obs_data_release(settings);

	if (!success) {
		if (output->ff_data.last_error) {
			obs_output_set_last_error(output->output,
						  output->ff_data.last_error);
		}
		ffmpeg_data_free(&output->ff_data);
		return false;
	}

	struct audio_convert_info aci = {.format =
						 output->ff_data.audio_format};

	output->active = true;

	if (!obs_output_can_begin_data_capture(output->output, 0))
		return false;

	ret = pthread_create(&output->write_thread, NULL, write_thread, output);
	if (ret != 0) {
		ffmpeg_log_error(LOG_WARNING, &output->ff_data,
				 "ffmpeg_output_start: failed to create write "
				 "thread.");
		ffmpeg_output_full_stop(output);
		return false;
	}

	obs_output_set_video_conversion(output->output, NULL);
	obs_output_set_audio_conversion(output->output, &aci);
	obs_output_begin_data_capture(output->output, 0);
	output->write_thread_active = true;
	return true;
}