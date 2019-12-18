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
struct ffmpeg_muxer {int /*<<< orphan*/  output; } ;
struct encoder_packet {int timebase_den; int /*<<< orphan*/  size; int /*<<< orphan*/  data; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  obs_encoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_ENCODER_VIDEO ; 
 int /*<<< orphan*/  obs_encoder_get_extra_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_output_get_video_encoder (int /*<<< orphan*/ ) ; 
 int write_packet (struct ffmpeg_muxer*,struct encoder_packet*) ; 

__attribute__((used)) static bool send_video_headers(struct ffmpeg_muxer *stream)
{
	obs_encoder_t *vencoder = obs_output_get_video_encoder(stream->output);

	struct encoder_packet packet = {.type = OBS_ENCODER_VIDEO,
					.timebase_den = 1};

	obs_encoder_get_extra_data(vencoder, &packet.data, &packet.size);
	return write_packet(stream, &packet);
}