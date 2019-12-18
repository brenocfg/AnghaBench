#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  frame_drop; int /*<<< orphan*/  video_frame_queue_size; int /*<<< orphan*/  video_packet_queue_size; int /*<<< orphan*/  audio_frame_queue_size; int /*<<< orphan*/  audio_packet_queue_size; } ;
struct ff_demuxer {TYPE_5__* video_decoder; int /*<<< orphan*/  video_callbacks; TYPE_1__ options; TYPE_5__* audio_decoder; int /*<<< orphan*/  audio_callbacks; } ;
struct TYPE_9__ {int hwaccel_decoder; int /*<<< orphan*/ * callbacks; int /*<<< orphan*/  natural_sync_clock; int /*<<< orphan*/  frame_drop; } ;
struct TYPE_8__ {int codec_type; } ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
#define  AVMEDIA_TYPE_AUDIO 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 int /*<<< orphan*/  AV_SYNC_AUDIO_MASTER ; 
 int /*<<< orphan*/  AV_SYNC_VIDEO_MASTER ; 
 int /*<<< orphan*/  ff_callbacks_format (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ff_decoder_free (TYPE_5__*) ; 
 void* ff_decoder_init (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool initialize_decoder(struct ff_demuxer *demuxer,
                               AVCodecContext *codec_context, AVStream *stream,
                               bool hwaccel_decoder)
{
	switch (codec_context->codec_type) {
	case AVMEDIA_TYPE_AUDIO:
		demuxer->audio_decoder = ff_decoder_init(
		        codec_context, stream,
		        demuxer->options.audio_packet_queue_size,
		        demuxer->options.audio_frame_queue_size);

		demuxer->audio_decoder->hwaccel_decoder = hwaccel_decoder;
		demuxer->audio_decoder->frame_drop =
		        demuxer->options.frame_drop;
		demuxer->audio_decoder->natural_sync_clock =
		        AV_SYNC_AUDIO_MASTER;
		demuxer->audio_decoder->callbacks = &demuxer->audio_callbacks;

		if (!ff_callbacks_format(&demuxer->audio_callbacks,
		                         codec_context)) {
			ff_decoder_free(demuxer->audio_decoder);
			demuxer->audio_decoder = NULL;
			return false;
		}

		demuxer->audio_decoder = demuxer->audio_decoder;
		return true;

	case AVMEDIA_TYPE_VIDEO:
		demuxer->video_decoder = ff_decoder_init(
		        codec_context, stream,
		        demuxer->options.video_packet_queue_size,
		        demuxer->options.video_frame_queue_size);

		demuxer->video_decoder->hwaccel_decoder = hwaccel_decoder;
		demuxer->video_decoder->frame_drop =
		        demuxer->options.frame_drop;
		demuxer->video_decoder->natural_sync_clock =
		        AV_SYNC_VIDEO_MASTER;
		demuxer->video_decoder->callbacks = &demuxer->video_callbacks;

		if (!ff_callbacks_format(&demuxer->video_callbacks,
		                         codec_context)) {
			ff_decoder_free(demuxer->video_decoder);
			demuxer->video_decoder = NULL;
			return false;
		}

		return true;
	default:
		return false;
	}
}