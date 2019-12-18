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
struct video_scale_info {int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct obs_encoder {int /*<<< orphan*/  media; int /*<<< orphan*/  mixer_idx; TYPE_1__ info; } ;
struct audio_convert_info {int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 scalar_t__ OBS_ENCODER_AUDIO ; 
 int /*<<< orphan*/  audio_output_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct audio_convert_info*,int /*<<< orphan*/ ,struct obs_encoder*) ; 
 int /*<<< orphan*/  get_audio_info (struct obs_encoder*,struct audio_convert_info*) ; 
 int /*<<< orphan*/  get_video_info (struct obs_encoder*,struct video_scale_info*) ; 
 scalar_t__ gpu_encode_available (struct obs_encoder*) ; 
 int /*<<< orphan*/  receive_audio ; 
 int /*<<< orphan*/  receive_video ; 
 int /*<<< orphan*/  set_encoder_active (struct obs_encoder*,int) ; 
 int /*<<< orphan*/  start_gpu_encode (struct obs_encoder*) ; 
 int /*<<< orphan*/  start_raw_video (int /*<<< orphan*/ ,struct video_scale_info*,int /*<<< orphan*/ ,struct obs_encoder*) ; 

__attribute__((used)) static void add_connection(struct obs_encoder *encoder)
{
	if (encoder->info.type == OBS_ENCODER_AUDIO) {
		struct audio_convert_info audio_info = {0};
		get_audio_info(encoder, &audio_info);

		audio_output_connect(encoder->media, encoder->mixer_idx,
				     &audio_info, receive_audio, encoder);
	} else {
		struct video_scale_info info = {0};
		get_video_info(encoder, &info);

		if (gpu_encode_available(encoder)) {
			start_gpu_encode(encoder);
		} else {
			start_raw_video(encoder->media, &info, receive_video,
					encoder);
		}
	}

	set_encoder_active(encoder, true);
}