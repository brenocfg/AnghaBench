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
struct obs_encoder {int first_received; scalar_t__ framesize_bytes; TYPE_1__* audio_input_buffer; int /*<<< orphan*/  samplerate; int /*<<< orphan*/  pause; int /*<<< orphan*/  first_raw_ts; } ;
struct audio_data {int /*<<< orphan*/  timestamp; } ;
struct TYPE_2__ {scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (size_t) ; 
 scalar_t__ audio_pause_check (int /*<<< orphan*/ *,struct audio_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_audio (struct obs_encoder*,struct audio_data*) ; 
 int /*<<< orphan*/  clear_audio (struct obs_encoder*) ; 
 int /*<<< orphan*/  profile_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  profile_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  receive_audio_name ; 
 int /*<<< orphan*/  send_audio_data (struct obs_encoder*) ; 

__attribute__((used)) static void receive_audio(void *param, size_t mix_idx, struct audio_data *in)
{
	profile_start(receive_audio_name);

	struct obs_encoder *encoder = param;
	struct audio_data audio = *in;

	if (!encoder->first_received) {
		encoder->first_raw_ts = audio.timestamp;
		encoder->first_received = true;
		clear_audio(encoder);
	}

	if (audio_pause_check(&encoder->pause, &audio, encoder->samplerate))
		goto end;

	if (!buffer_audio(encoder, &audio))
		goto end;

	while (encoder->audio_input_buffer[0].size >=
	       encoder->framesize_bytes) {
		if (!send_audio_data(encoder)) {
			break;
		}
	}

	UNUSED_PARAMETER(mix_idx);

end:
	profile_end(receive_audio_name);
}