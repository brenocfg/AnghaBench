#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ff_demuxer {TYPE_1__* audio_decoder; TYPE_2__* video_decoder; } ;
struct TYPE_4__ {int /*<<< orphan*/  packet_queue; int /*<<< orphan*/ * stream; } ;
struct TYPE_3__ {int /*<<< orphan*/  packet_queue; int /*<<< orphan*/ * stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  packet_queue_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_queue_put_flush_packet (int /*<<< orphan*/ *) ; 

void ff_demuxer_flush(struct ff_demuxer *demuxer)
{
	if (demuxer->video_decoder != NULL &&
	    demuxer->video_decoder->stream != NULL) {
		packet_queue_flush(&demuxer->video_decoder->packet_queue);
		packet_queue_put_flush_packet(
		        &demuxer->video_decoder->packet_queue);
	}

	if (demuxer->audio_decoder != NULL &&
	    demuxer->audio_decoder->stream != NULL) {
		packet_queue_flush(&demuxer->audio_decoder->packet_queue);
		packet_queue_put_flush_packet(
		        &demuxer->audio_decoder->packet_queue);
	}
}