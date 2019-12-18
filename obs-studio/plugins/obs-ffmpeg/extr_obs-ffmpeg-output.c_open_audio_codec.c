#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  audio_settings; } ;
struct ffmpeg_data {int frame_size; int /*<<< orphan*/ * samples; int /*<<< orphan*/  acodec; TYPE_6__** aframe; TYPE_2__ config; TYPE_1__** audio_streams; } ;
struct TYPE_10__ {int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  channels; int /*<<< orphan*/  format; } ;
struct TYPE_9__ {int strict_std_compliance; int frame_size; int /*<<< orphan*/  sample_fmt; int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channel_layout; } ;
struct TYPE_7__ {TYPE_3__* codec; } ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 TYPE_6__* av_frame_alloc () ; 
 int av_samples_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int avcodec_open2 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffmpeg_log_error (int /*<<< orphan*/ ,struct ffmpeg_data*,char*,...) ; 
 int /*<<< orphan*/  parse_params (TYPE_3__*,char**) ; 
 int /*<<< orphan*/  strlist_free (char**) ; 
 char** strlist_split (int /*<<< orphan*/ ,char,int) ; 

__attribute__((used)) static bool open_audio_codec(struct ffmpeg_data *data, int idx)
{
	AVCodecContext *context = data->audio_streams[idx]->codec;
	char **opts = strlist_split(data->config.audio_settings, ' ', false);
	int ret;

	if (opts) {
		parse_params(context, opts);
		strlist_free(opts);
	}

	data->aframe[idx] = av_frame_alloc();
	if (!data->aframe[idx]) {
		ffmpeg_log_error(LOG_WARNING, data,
				 "Failed to allocate audio frame");
		return false;
	}

	data->aframe[idx]->format = context->sample_fmt;
	data->aframe[idx]->channels = context->channels;
	data->aframe[idx]->channel_layout = context->channel_layout;
	data->aframe[idx]->sample_rate = context->sample_rate;

	context->strict_std_compliance = -2;

	ret = avcodec_open2(context, data->acodec, NULL);
	if (ret < 0) {
		ffmpeg_log_error(LOG_WARNING, data,
				 "Failed to open audio codec: %s",
				 av_err2str(ret));
		return false;
	}

	data->frame_size = context->frame_size ? context->frame_size : 1024;

	ret = av_samples_alloc(data->samples[idx], NULL, context->channels,
			       data->frame_size, context->sample_fmt, 0);
	if (ret < 0) {
		ffmpeg_log_error(LOG_WARNING, data,
				 "Failed to create audio buffer: %s",
				 av_err2str(ret));
		return false;
	}

	return true;
}