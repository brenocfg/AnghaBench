#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  color_range; int /*<<< orphan*/  color_space; int /*<<< orphan*/  video_settings; } ;
struct ffmpeg_data {TYPE_7__* vframe; TYPE_2__ config; TYPE_6__* vcodec; TYPE_1__* video; } ;
struct TYPE_13__ {int /*<<< orphan*/  color_range; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  format; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/  priv_data; } ;
struct TYPE_9__ {TYPE_3__* codec; } ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 TYPE_7__* av_frame_alloc () ; 
 int av_frame_get_buffer (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_opt_set (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int avcodec_open2 (TYPE_3__*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  base_get_alignment () ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ffmpeg_log_error (int /*<<< orphan*/ ,struct ffmpeg_data*,char*,...) ; 
 int /*<<< orphan*/  parse_params (TYPE_3__*,char**) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlist_free (char**) ; 
 char** strlist_split (int /*<<< orphan*/ ,char,int) ; 

__attribute__((used)) static bool open_video_codec(struct ffmpeg_data *data)
{
	AVCodecContext *context = data->video->codec;
	char **opts = strlist_split(data->config.video_settings, ' ', false);
	int ret;

	if (strcmp(data->vcodec->name, "libx264") == 0)
		av_opt_set(context->priv_data, "preset", "veryfast", 0);

	if (opts) {
		// libav requires x264 parameters in a special format which may be non-obvious
		if (!parse_params(context, opts) &&
		    strcmp(data->vcodec->name, "libx264") == 0)
			blog(LOG_WARNING,
			     "If you're trying to set x264 parameters, use x264-params=name=value:name=value");
		strlist_free(opts);
	}

	ret = avcodec_open2(context, data->vcodec, NULL);
	if (ret < 0) {
		ffmpeg_log_error(LOG_WARNING, data,
				 "Failed to open video codec: %s",
				 av_err2str(ret));
		return false;
	}

	data->vframe = av_frame_alloc();
	if (!data->vframe) {
		ffmpeg_log_error(LOG_WARNING, data,
				 "Failed to allocate video frame");
		return false;
	}

	data->vframe->format = context->pix_fmt;
	data->vframe->width = context->width;
	data->vframe->height = context->height;
	data->vframe->colorspace = data->config.color_space;
	data->vframe->color_range = data->config.color_range;

	ret = av_frame_get_buffer(data->vframe, base_get_alignment());
	if (ret < 0) {
		ffmpeg_log_error(LOG_WARNING, data,
				 "Failed to allocate vframe: %s",
				 av_err2str(ret));
		return false;
	}

	return true;
}