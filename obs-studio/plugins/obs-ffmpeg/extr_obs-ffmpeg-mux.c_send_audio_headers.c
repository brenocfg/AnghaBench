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
struct ffmpeg_muxer {int dummy; } ;
struct encoder_packet {int timebase_den; size_t track_idx; int /*<<< orphan*/  size; int /*<<< orphan*/  data; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  obs_encoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_ENCODER_AUDIO ; 
 int /*<<< orphan*/  obs_encoder_get_extra_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int write_packet (struct ffmpeg_muxer*,struct encoder_packet*) ; 

__attribute__((used)) static bool send_audio_headers(struct ffmpeg_muxer *stream,
			       obs_encoder_t *aencoder, size_t idx)
{
	struct encoder_packet packet = {
		.type = OBS_ENCODER_AUDIO, .timebase_den = 1, .track_idx = idx};

	obs_encoder_get_extra_data(aencoder, &packet.data, &packet.size);
	return write_packet(stream, &packet);
}