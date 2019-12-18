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
struct TYPE_2__ {int sync_type; int /*<<< orphan*/ * opaque; void* sync_clock; } ;
struct ff_demuxer {TYPE_1__ clock; int /*<<< orphan*/ * video_decoder; int /*<<< orphan*/ * audio_decoder; } ;

/* Variables and functions */
#define  AV_SYNC_AUDIO_MASTER 130 
#define  AV_SYNC_EXTERNAL_MASTER 129 
#define  AV_SYNC_VIDEO_MASTER 128 
 void* ff_decoder_clock ; 
 void* ff_external_clock ; 

__attribute__((used)) static bool set_clock_sync_type(struct ff_demuxer *demuxer)
{
	if (demuxer->video_decoder == NULL) {
		if (demuxer->clock.sync_type == AV_SYNC_VIDEO_MASTER)
			demuxer->clock.sync_type = AV_SYNC_AUDIO_MASTER;
	}

	if (demuxer->audio_decoder == NULL) {
		if (demuxer->clock.sync_type == AV_SYNC_AUDIO_MASTER)
			demuxer->clock.sync_type = AV_SYNC_VIDEO_MASTER;
	}

	switch (demuxer->clock.sync_type) {
	case AV_SYNC_AUDIO_MASTER:
		demuxer->clock.sync_clock = ff_decoder_clock;
		demuxer->clock.opaque = demuxer->audio_decoder;
		break;
	case AV_SYNC_VIDEO_MASTER:
		demuxer->clock.sync_clock = ff_decoder_clock;
		demuxer->clock.opaque = demuxer->video_decoder;
		break;
	case AV_SYNC_EXTERNAL_MASTER:
		demuxer->clock.sync_clock = ff_external_clock;
		demuxer->clock.opaque = NULL;
		break;
	default:
		return false;
	}

	return true;
}