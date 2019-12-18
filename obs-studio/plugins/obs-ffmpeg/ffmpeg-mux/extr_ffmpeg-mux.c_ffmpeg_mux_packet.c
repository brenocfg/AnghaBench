#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ffmpeg_mux {int /*<<< orphan*/  output; } ;
struct ffm_packet_info {scalar_t__ keyframe; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; scalar_t__ size; } ;
struct TYPE_4__ {int size; int stream_index; int /*<<< orphan*/  flags; void* dts; void* pts; int /*<<< orphan*/ * data; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  av_init_packet (TYPE_1__*) ; 
 scalar_t__ av_interleaved_write_frame (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int get_index (struct ffmpeg_mux*,struct ffm_packet_info*) ; 
 void* rescale_ts (struct ffmpeg_mux*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline bool ffmpeg_mux_packet(struct ffmpeg_mux *ffm, uint8_t *buf,
				     struct ffm_packet_info *info)
{
	int idx = get_index(ffm, info);
	AVPacket packet = {0};

	/* The muxer might not support video/audio, or multiple audio tracks */
	if (idx == -1) {
		return true;
	}

	av_init_packet(&packet);

	packet.data = buf;
	packet.size = (int)info->size;
	packet.stream_index = idx;
	packet.pts = rescale_ts(ffm, info->pts, idx);
	packet.dts = rescale_ts(ffm, info->dts, idx);

	if (info->keyframe)
		packet.flags = AV_PKT_FLAG_KEY;

	return av_interleaved_write_frame(ffm->output, &packet) >= 0;
}