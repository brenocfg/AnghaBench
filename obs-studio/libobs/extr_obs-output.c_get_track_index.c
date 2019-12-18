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
struct obs_output {struct obs_encoder** audio_encoders; } ;
struct obs_encoder {int dummy; } ;
struct encoder_packet {struct obs_encoder* encoder; } ;

/* Variables and functions */
 size_t MAX_AUDIO_MIXES ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static size_t get_track_index(const struct obs_output *output,
			      struct encoder_packet *pkt)
{
	for (size_t i = 0; i < MAX_AUDIO_MIXES; i++) {
		struct obs_encoder *encoder = output->audio_encoders[i];

		if (pkt->encoder == encoder)
			return i;
	}

	assert(false);
	return 0;
}