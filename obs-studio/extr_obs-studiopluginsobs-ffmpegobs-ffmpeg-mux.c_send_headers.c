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
typedef  int /*<<< orphan*/  obs_encoder_t ;

/* Variables and functions */
 int /*<<< orphan*/ * obs_output_get_audio_encoder (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  send_audio_headers (struct ffmpeg_muxer*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  send_video_headers (struct ffmpeg_muxer*) ; 

__attribute__((used)) static bool send_headers(struct ffmpeg_muxer *stream)
{
	obs_encoder_t *aencoder;
	size_t idx = 0;

	if (!send_video_headers(stream))
		return false;

	do {
		aencoder = obs_output_get_audio_encoder(stream->output, idx);
		if (aencoder) {
			if (!send_audio_headers(stream, aencoder, idx)) {
				return false;
			}
			idx++;
		}
	} while (aencoder);

	return true;
}