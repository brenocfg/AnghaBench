#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_4__* fmt; } ;
struct ffmpeg_source {TYPE_1__ media; } ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  calldata_t ;
struct TYPE_8__ {scalar_t__ duration; TYPE_2__** streams; } ;
struct TYPE_7__ {scalar_t__ den; scalar_t__ num; } ;
struct TYPE_6__ {scalar_t__ nb_frames; TYPE_3__ avg_frame_rate; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVRational ;

/* Variables and functions */
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_TIME_BASE ; 
 int /*<<< orphan*/  FF_BLOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int av_find_best_stream (TYPE_4__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calldata_set_int (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ ceil (double) ; 

__attribute__((used)) static void get_nb_frames(void *data, calldata_t *cd)
{
	struct ffmpeg_source *s = data;
	int64_t frames = 0;

	if (!s->media.fmt) {
		calldata_set_int(cd, "num_frames", frames);
		return;
	}

	int video_stream_index = av_find_best_stream(
		s->media.fmt, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);

	if (video_stream_index < 0) {
		FF_BLOG(LOG_WARNING, "Getting number of frames failed: No "
				     "video stream in media file!");
		calldata_set_int(cd, "num_frames", frames);
		return;
	}

	AVStream *stream = s->media.fmt->streams[video_stream_index];

	if (stream->nb_frames > 0) {
		frames = stream->nb_frames;
	} else {
		FF_BLOG(LOG_DEBUG, "nb_frames not set, estimating using frame "
				   "rate and duration");
		AVRational avg_frame_rate = stream->avg_frame_rate;
		frames = (int64_t)ceil((double)s->media.fmt->duration /
				       (double)AV_TIME_BASE *
				       (double)avg_frame_rate.num /
				       (double)avg_frame_rate.den);
	}

	calldata_set_int(cd, "num_frames", frames);
}