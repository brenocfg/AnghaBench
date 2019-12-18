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
struct TYPE_2__ {scalar_t__ type; } ;
struct obs_encoder {int /*<<< orphan*/  media; int /*<<< orphan*/  mixer_idx; TYPE_1__ info; } ;

/* Variables and functions */
 scalar_t__ OBS_ENCODER_AUDIO ; 
 int /*<<< orphan*/  audio_output_disconnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct obs_encoder*) ; 
 scalar_t__ gpu_encode_available (struct obs_encoder*) ; 
 int /*<<< orphan*/  obs_encoder_shutdown (struct obs_encoder*) ; 
 int /*<<< orphan*/  receive_audio ; 
 int /*<<< orphan*/  receive_video ; 
 int /*<<< orphan*/  set_encoder_active (struct obs_encoder*,int) ; 
 int /*<<< orphan*/  stop_gpu_encode (struct obs_encoder*) ; 
 int /*<<< orphan*/  stop_raw_video (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct obs_encoder*) ; 

__attribute__((used)) static void remove_connection(struct obs_encoder *encoder, bool shutdown)
{
	if (encoder->info.type == OBS_ENCODER_AUDIO) {
		audio_output_disconnect(encoder->media, encoder->mixer_idx,
					receive_audio, encoder);
	} else {
		if (gpu_encode_available(encoder)) {
			stop_gpu_encode(encoder);
		} else {
			stop_raw_video(encoder->media, receive_video, encoder);
		}
	}

	/* obs_encoder_shutdown locks init_mutex, so don't call it on encode
	 * errors, otherwise you can get a deadlock with outputs when they end
	 * data capture, which will lock init_mutex and the video callback
	 * mutex in the reverse order.  instead, call shutdown before starting
	 * up again */
	if (shutdown)
		obs_encoder_shutdown(encoder);
	set_encoder_active(encoder, false);
}