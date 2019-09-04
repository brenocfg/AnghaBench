#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct obs_source_frame2 {int format; int flip; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  color_range_max; int /*<<< orphan*/  color_range_min; int /*<<< orphan*/  color_matrix; int /*<<< orphan*/  range; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct ffmpeg_decode {TYPE_4__* frame; int /*<<< orphan*/  decoder; TYPE_1__* codec; int /*<<< orphan*/  packet_buffer; } ;
typedef  enum video_format { ____Placeholder_video_format } video_format ;
struct TYPE_9__ {scalar_t__ color_range; long long pkt_pts; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  format; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {int size; long long pts; int /*<<< orphan*/  flags; int /*<<< orphan*/  data; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {scalar_t__ id; } ;
typedef  TYPE_2__ AVPacket ;

/* Variables and functions */
 scalar_t__ AVCOL_RANGE_JPEG ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 scalar_t__ AV_CODEC_ID_H264 ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 size_t MAX_AV_PLANES ; 
 int /*<<< orphan*/  VIDEO_CS_601 ; 
 scalar_t__ VIDEO_FORMAT_NONE ; 
 int /*<<< orphan*/  VIDEO_RANGE_DEFAULT ; 
 int /*<<< orphan*/  VIDEO_RANGE_FULL ; 
 TYPE_4__* av_frame_alloc () ; 
 int /*<<< orphan*/  av_init_packet (TYPE_2__*) ; 
 int avcodec_receive_frame (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int avcodec_send_packet (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int convert_pixel_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_data (struct ffmpeg_decode*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ obs_avc_keyframe (int /*<<< orphan*/ *,size_t) ; 
 int video_format_get_parameters (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool ffmpeg_decode_video(struct ffmpeg_decode *decode,
		uint8_t *data, size_t size, long long *ts,
		struct obs_source_frame2 *frame,
		bool *got_output)
{
	AVPacket packet = {0};
	int got_frame = false;
	enum video_format new_format;
	int ret;

	*got_output = false;

	copy_data(decode, data, size);

	av_init_packet(&packet);
	packet.data     = decode->packet_buffer;
	packet.size     = (int)size;
	packet.pts      = *ts;

	if (decode->codec->id == AV_CODEC_ID_H264 &&
			obs_avc_keyframe(data, size))
		packet.flags |= AV_PKT_FLAG_KEY;

	if (!decode->frame) {
		decode->frame = av_frame_alloc();
		if (!decode->frame)
			return false;
	}

	ret = avcodec_send_packet(decode->decoder, &packet);
	if (ret == 0)
		ret = avcodec_receive_frame(decode->decoder, decode->frame);

	got_frame = (ret == 0);

	if (ret == AVERROR_EOF || ret == AVERROR(EAGAIN))
		ret = 0;

	if (ret < 0)
		return false;
	else if (!got_frame)
		return true;

	for (size_t i = 0; i < MAX_AV_PLANES; i++) {
		frame->data[i]     = decode->frame->data[i];
		frame->linesize[i] = decode->frame->linesize[i];
	}

	new_format = convert_pixel_format(decode->frame->format);
	if (new_format != frame->format) {
		bool success;

		frame->format = new_format;
		frame->range = decode->frame->color_range == AVCOL_RANGE_JPEG
			? VIDEO_RANGE_FULL
			: VIDEO_RANGE_DEFAULT;

		success = video_format_get_parameters(VIDEO_CS_601,
				frame->range, frame->color_matrix,
				frame->color_range_min, frame->color_range_max);
		if (!success) {
			blog(LOG_ERROR, "Failed to get video format "
			                "parameters for video format %u",
			                VIDEO_CS_601);
			return false;
		}
	}

	*ts = decode->frame->pkt_pts;

	frame->width  = decode->frame->width;
	frame->height = decode->frame->height;
	frame->flip   = false;

	if (frame->format == VIDEO_FORMAT_NONE)
		return false;

	*got_output = true;
	return true;
}