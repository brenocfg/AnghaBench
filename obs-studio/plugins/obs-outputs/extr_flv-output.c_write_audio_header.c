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
struct flv_output {int /*<<< orphan*/ * output; } ;
struct encoder_packet {int timebase_den; int /*<<< orphan*/  size; int /*<<< orphan*/  data; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  obs_output_t ;
typedef  int /*<<< orphan*/  obs_encoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_ENCODER_AUDIO ; 
 int /*<<< orphan*/  obs_encoder_get_extra_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_output_get_audio_encoder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_packet (struct flv_output*,struct encoder_packet*,int) ; 

__attribute__((used)) static void write_audio_header(struct flv_output *stream)
{
	obs_output_t *context = stream->output;
	obs_encoder_t *aencoder = obs_output_get_audio_encoder(context, 0);

	struct encoder_packet packet = {.type = OBS_ENCODER_AUDIO,
					.timebase_den = 1};

	obs_encoder_get_extra_data(aencoder, &packet.data, &packet.size);
	write_packet(stream, &packet, true);
}