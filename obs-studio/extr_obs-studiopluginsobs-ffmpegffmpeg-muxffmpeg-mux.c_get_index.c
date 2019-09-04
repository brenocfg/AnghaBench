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
struct ffmpeg_mux {int num_audio_streams; TYPE_2__** audio_streams; TYPE_1__* video_stream; } ;
struct ffm_packet_info {scalar_t__ type; size_t index; } ;
struct TYPE_4__ {int id; } ;
struct TYPE_3__ {int id; } ;

/* Variables and functions */
 scalar_t__ FFM_PACKET_VIDEO ; 

__attribute__((used)) static inline int get_index(struct ffmpeg_mux *ffm,
		struct ffm_packet_info *info)
{
	if (info->type == FFM_PACKET_VIDEO) {
		if (ffm->video_stream) {
			return ffm->video_stream->id;
		}
	} else {
		if ((int)info->index < ffm->num_audio_streams) {
			return ffm->audio_streams[info->index]->id;
		}
	}

	return -1;
}