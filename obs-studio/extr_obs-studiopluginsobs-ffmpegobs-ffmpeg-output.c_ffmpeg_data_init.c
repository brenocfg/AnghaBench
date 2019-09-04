#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ffmpeg_cfg {char* url; char* format_name; char* format_mime_type; int /*<<< orphan*/  audio_tracks; int /*<<< orphan*/  audio_mix_count; } ;
struct ffmpeg_data {int initialized; TYPE_2__* output; struct ffmpeg_cfg config; int /*<<< orphan*/  audio_tracks; int /*<<< orphan*/  num_audio_streams; } ;
struct TYPE_5__ {TYPE_1__* oformat; } ;
struct TYPE_4__ {int /*<<< orphan*/  audio_codec; int /*<<< orphan*/  video_codec; } ;
typedef  int /*<<< orphan*/  AVOutputFormat ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CODEC_ID_AAC ; 
 int /*<<< orphan*/  AV_CODEC_ID_H264 ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ astrcmpi_n (char*,char*,int) ; 
 int /*<<< orphan*/  av_dump_format (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * av_guess_format (char*,char*,char*) ; 
 int /*<<< orphan*/  av_register_all () ; 
 int /*<<< orphan*/  avformat_alloc_output_context2 (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avformat_network_init () ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ffmpeg_log_error (int /*<<< orphan*/ ,struct ffmpeg_data*,char*,...) ; 
 int /*<<< orphan*/  init_streams (struct ffmpeg_data*) ; 
 int /*<<< orphan*/  memset (struct ffmpeg_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  open_output_file (struct ffmpeg_data*) ; 
 int /*<<< orphan*/  safe_str (char*) ; 
 int /*<<< orphan*/  set_encoder_ids (struct ffmpeg_data*) ; 

__attribute__((used)) static bool ffmpeg_data_init(struct ffmpeg_data *data,
		struct ffmpeg_cfg *config)
{
	bool is_rtmp = false;

	memset(data, 0, sizeof(struct ffmpeg_data));
	data->config = *config;
	data->num_audio_streams = config->audio_mix_count;
	data->audio_tracks = config->audio_tracks;
	if (!config->url || !*config->url)
		return false;

	av_register_all();
	avformat_network_init();

	is_rtmp = (astrcmpi_n(config->url, "rtmp://", 7) == 0);

	AVOutputFormat *output_format = av_guess_format(
			is_rtmp ? "flv" : data->config.format_name,
			data->config.url,
			is_rtmp ? NULL : data->config.format_mime_type);

	if (output_format == NULL) {
		ffmpeg_log_error(LOG_WARNING, data,
			"Couldn't find matching output format with "
			"parameters: name=%s, url=%s, mime=%s",
			safe_str(is_rtmp ?
				"flv" : data->config.format_name),
			safe_str(data->config.url),
			safe_str(is_rtmp ?
				NULL : data->config.format_mime_type));

		goto fail;
	}

	avformat_alloc_output_context2(&data->output, output_format,
			NULL, NULL);

	if (!data->output) {
		ffmpeg_log_error(LOG_WARNING, data,
			"Couldn't create avformat context");
		goto fail;
	}

	if (is_rtmp) {
		data->output->oformat->video_codec = AV_CODEC_ID_H264;
		data->output->oformat->audio_codec = AV_CODEC_ID_AAC;
	} else {
		if (data->config.format_name)
			set_encoder_ids(data);
	}

	if (!init_streams(data))
		goto fail;
	if (!open_output_file(data))
		goto fail;

	av_dump_format(data->output, 0, NULL, 1);

	data->initialized = true;
	return true;

fail:
	blog(LOG_WARNING, "ffmpeg_data_init failed");
	return false;
}