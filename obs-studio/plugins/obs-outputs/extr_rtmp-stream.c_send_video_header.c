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
typedef  int /*<<< orphan*/  uint8_t ;
struct rtmp_stream {int /*<<< orphan*/ * output; } ;
struct encoder_packet {int timebase_den; int keyframe; int /*<<< orphan*/  data; int /*<<< orphan*/  size; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  obs_output_t ;
typedef  int /*<<< orphan*/  obs_encoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_ENCODER_VIDEO ; 
 int /*<<< orphan*/  obs_encoder_get_extra_data (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/ * obs_output_get_video_encoder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_parse_avc_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ send_packet (struct rtmp_stream*,struct encoder_packet*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool send_video_header(struct rtmp_stream *stream)
{
	obs_output_t *context = stream->output;
	obs_encoder_t *vencoder = obs_output_get_video_encoder(context);
	uint8_t *header;
	size_t size;

	struct encoder_packet packet = {
		.type = OBS_ENCODER_VIDEO, .timebase_den = 1, .keyframe = true};

	obs_encoder_get_extra_data(vencoder, &header, &size);
	packet.size = obs_parse_avc_header(&packet.data, header, size);
	return send_packet(stream, &packet, true, 0) >= 0;
}