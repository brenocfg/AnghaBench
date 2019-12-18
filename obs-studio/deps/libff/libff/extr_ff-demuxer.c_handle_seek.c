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
struct ff_demuxer {int seek_request; scalar_t__ seek_flush; scalar_t__ seek_pos; int /*<<< orphan*/  seek_flags; TYPE_4__* format_context; TYPE_2__* audio_decoder; TYPE_1__* video_decoder; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_8__ {scalar_t__ duration; } ;
struct TYPE_7__ {int /*<<< orphan*/  time_base; } ;
struct TYPE_6__ {TYPE_3__* stream; } ;
struct TYPE_5__ {TYPE_3__* stream; } ;
typedef  TYPE_3__ AVStream ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int av_seek_frame (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_demuxer_flush (struct ff_demuxer*) ; 
 int /*<<< orphan*/  ff_demuxer_reset (struct ff_demuxer*) ; 

__attribute__((used)) static bool handle_seek(struct ff_demuxer *demuxer)
{
	int ret;

	if (demuxer->seek_request) {
		AVStream *seek_stream = NULL;
		int64_t seek_target = demuxer->seek_pos;

		if (demuxer->video_decoder != NULL) {
			seek_stream = demuxer->video_decoder->stream;

		} else if (demuxer->audio_decoder != NULL) {
			seek_stream = demuxer->audio_decoder->stream;
		}

		if (seek_stream != NULL &&
		    demuxer->format_context->duration != AV_NOPTS_VALUE) {
			seek_target = av_rescale_q(seek_target, AV_TIME_BASE_Q,
			                           seek_stream->time_base);
		}

		ret = av_seek_frame(demuxer->format_context, 0, seek_target,
		                    demuxer->seek_flags);
		if (ret < 0) {
			av_log(NULL, AV_LOG_ERROR, "unable to seek stream: %s",
			       av_err2str(ret));
			demuxer->seek_pos = 0;
			demuxer->seek_request = false;
			return false;

		} else {
			if (demuxer->seek_flush)
				ff_demuxer_flush(demuxer);
			ff_demuxer_reset(demuxer);
		}

		demuxer->seek_request = false;
	}
	return true;
}