#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ff_packet {int /*<<< orphan*/  base; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {scalar_t__ is_looping; } ;
struct ff_demuxer {int abort; TYPE_4__* video_decoder; TYPE_4__* audio_decoder; TYPE_1__ options; TYPE_3__* format_context; int /*<<< orphan*/  input; } ;
struct TYPE_11__ {int eof; } ;
struct TYPE_10__ {TYPE_2__* pb; } ;
struct TYPE_9__ {scalar_t__ error; scalar_t__ eof_reached; } ;
typedef  TYPE_2__ AVIOContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_dump_format (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int /*<<< orphan*/  av_free_packet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int av_read_frame (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_usleep (int) ; 
 scalar_t__ ff_decoder_accept (TYPE_4__*,struct ff_packet*) ; 
 scalar_t__ ff_decoder_full (TYPE_4__*) ; 
 int /*<<< orphan*/  ff_demuxer_reset (struct ff_demuxer*) ; 
 int /*<<< orphan*/  find_and_initialize_stream_decoders (struct ff_demuxer*) ; 
 int /*<<< orphan*/  handle_seek (struct ff_demuxer*) ; 
 int /*<<< orphan*/  open_input (struct ff_demuxer*,TYPE_3__**) ; 
 int /*<<< orphan*/  seek_beginning (struct ff_demuxer*) ; 

__attribute__((used)) static void *demux_thread(void *opaque)
{
	struct ff_demuxer *demuxer = (struct ff_demuxer *)opaque;
	int result;

	struct ff_packet packet = {0};

	if (!open_input(demuxer, &demuxer->format_context))
		goto fail;

	av_dump_format(demuxer->format_context, 0, demuxer->input, 0);

	if (!find_and_initialize_stream_decoders(demuxer))
		goto fail;

	ff_demuxer_reset(demuxer);

	while (!demuxer->abort) {
		// failed to seek (looping?)
		if (!handle_seek(demuxer))
			break;

		if (ff_decoder_full(demuxer->audio_decoder) ||
		    ff_decoder_full(demuxer->video_decoder)) {
			av_usleep(10 * 1000); // 10ms
			continue;
		}

		result = av_read_frame(demuxer->format_context, &packet.base);
		if (result < 0) {
			bool eof = false;
			if (result == AVERROR_EOF) {
				eof = true;
			} else if (demuxer->format_context->pb != NULL) {
				AVIOContext *io_context =
				        demuxer->format_context->pb;
				if (io_context->error == 0) {
					av_usleep(100 * 1000); // 100ms
					continue;
				} else {
					if (io_context->eof_reached != 0)
						eof = true;
				}
			}

			if (eof) {
				if (demuxer->options.is_looping) {
					seek_beginning(demuxer);
				} else {
					break;
				}
				continue;
			} else {
				av_log(NULL, AV_LOG_ERROR,
				       "av_read_frame() failed: %s",
				       av_err2str(result));
				break;
			}
		}

		if (ff_decoder_accept(demuxer->video_decoder, &packet))
			continue;
		else if (ff_decoder_accept(demuxer->audio_decoder, &packet))
			continue;
		else
			av_free_packet(&packet.base);
	}
	if (demuxer->audio_decoder != NULL)
		demuxer->audio_decoder->eof = true;
	if (demuxer->video_decoder != NULL)
		demuxer->video_decoder->eof = true;
fail:
	demuxer->abort = true;

	return NULL;
}