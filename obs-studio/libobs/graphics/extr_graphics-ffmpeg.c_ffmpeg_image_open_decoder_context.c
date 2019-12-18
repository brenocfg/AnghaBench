#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ffmpeg_image {int stream_idx; int /*<<< orphan*/  file; int /*<<< orphan*/  decoder; TYPE_2__* decoder_ctx; TYPE_1__* stream; TYPE_3__* fmt_ctx; } ;
struct TYPE_6__ {TYPE_1__** streams; } ;
struct TYPE_5__ {int /*<<< orphan*/  codec_id; } ;
struct TYPE_4__ {TYPE_2__* codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int av_find_best_stream (TYPE_3__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avcodec_find_decoder (int /*<<< orphan*/ ) ; 
 int avcodec_open2 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static bool ffmpeg_image_open_decoder_context(struct ffmpeg_image *info)
{
	int ret = av_find_best_stream(info->fmt_ctx, AVMEDIA_TYPE_VIDEO, -1, 1,
				      NULL, 0);
	if (ret < 0) {
		blog(LOG_WARNING, "Couldn't find video stream in file '%s': %s",
		     info->file, av_err2str(ret));
		return false;
	}

	info->stream_idx = ret;
	info->stream = info->fmt_ctx->streams[ret];
	info->decoder_ctx = info->stream->codec;
	info->decoder = avcodec_find_decoder(info->decoder_ctx->codec_id);

	if (!info->decoder) {
		blog(LOG_WARNING, "Failed to find decoder for file '%s'",
		     info->file);
		return false;
	}

	ret = avcodec_open2(info->decoder_ctx, info->decoder, NULL);
	if (ret < 0) {
		blog(LOG_WARNING,
		     "Failed to open video codec for file '%s': "
		     "%s",
		     info->file, av_err2str(ret));
		return false;
	}

	return true;
}