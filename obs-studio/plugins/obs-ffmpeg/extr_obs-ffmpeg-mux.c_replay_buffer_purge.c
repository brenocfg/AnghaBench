#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct ffmpeg_muxer {scalar_t__ max_size; int keyframes; scalar_t__ cur_size; scalar_t__ cur_time; scalar_t__ max_time; TYPE_1__ packets; } ;
struct encoder_packet {scalar_t__ dts_usec; scalar_t__ size; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  purge (struct ffmpeg_muxer*) ; 

__attribute__((used)) static inline void replay_buffer_purge(struct ffmpeg_muxer *stream,
				       struct encoder_packet *pkt)
{
	if (stream->max_size) {
		if (!stream->packets.size || stream->keyframes <= 2)
			return;

		while ((stream->cur_size + (int64_t)pkt->size) >
		       stream->max_size)
			purge(stream);
	}

	if (!stream->packets.size || stream->keyframes <= 2)
		return;

	while ((pkt->dts_usec - stream->cur_time) > stream->max_time)
		purge(stream);
}