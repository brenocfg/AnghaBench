#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ftl_stream {scalar_t__ min_priority; int /*<<< orphan*/  last_dts_usec; int /*<<< orphan*/  dropped_frames; } ;
struct encoder_packet {scalar_t__ priority; int /*<<< orphan*/  dts_usec; } ;

/* Variables and functions */
 int add_packet (struct ftl_stream*,struct encoder_packet*) ; 
 int /*<<< orphan*/  check_to_drop_frames (struct ftl_stream*,int) ; 

__attribute__((used)) static bool add_video_packet(struct ftl_stream *stream,
			     struct encoder_packet *packet)
{
	check_to_drop_frames(stream, false);
	check_to_drop_frames(stream, true);

	/* if currently dropping frames, drop packets until it reaches the
	 * desired priority */
	if (packet->priority < stream->min_priority) {
		stream->dropped_frames++;
		return false;
	} else {
		stream->min_priority = 0;
	}

	stream->last_dts_usec = packet->dts_usec;
	return add_packet(stream, packet);
}