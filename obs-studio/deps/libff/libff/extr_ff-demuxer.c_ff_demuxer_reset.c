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
struct ff_packet {struct ff_clock* clock; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  opaque; int /*<<< orphan*/  sync_clock; int /*<<< orphan*/  sync_type; } ;
struct ff_demuxer {TYPE_3__* video_decoder; TYPE_2__* audio_decoder; TYPE_1__ clock; } ;
struct ff_clock {int /*<<< orphan*/  opaque; int /*<<< orphan*/  sync_clock; int /*<<< orphan*/  sync_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  packet_queue; } ;
struct TYPE_5__ {int /*<<< orphan*/  packet_queue; } ;

/* Variables and functions */
 struct ff_clock* ff_clock_init () ; 
 int /*<<< orphan*/  ff_clock_retain (struct ff_clock*) ; 
 int /*<<< orphan*/  packet_queue_put (int /*<<< orphan*/ *,struct ff_packet*) ; 

void ff_demuxer_reset(struct ff_demuxer *demuxer)
{
	struct ff_packet packet = {0};
	struct ff_clock *clock = ff_clock_init();
	clock->sync_type = demuxer->clock.sync_type;
	clock->sync_clock = demuxer->clock.sync_clock;
	clock->opaque = demuxer->clock.opaque;

	packet.clock = clock;

	if (demuxer->audio_decoder != NULL) {
		ff_clock_retain(clock);
		packet_queue_put(&demuxer->audio_decoder->packet_queue,
		                 &packet);
	}

	if (demuxer->video_decoder != NULL) {
		ff_clock_retain(clock);
		packet_queue_put(&demuxer->video_decoder->packet_queue,
		                 &packet);
	}
}