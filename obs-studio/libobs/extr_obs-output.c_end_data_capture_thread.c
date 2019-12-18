#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  end_data_capture_thread_active; int /*<<< orphan*/  stopping_event; int /*<<< orphan*/  active; scalar_t__ active_delay_ns; int /*<<< orphan*/  service; int /*<<< orphan*/  video; int /*<<< orphan*/  video_encoder; } ;
typedef  TYPE_1__ obs_output_t ;
typedef  int /*<<< orphan*/  encoded_callback_t ;

/* Variables and functions */
 int /*<<< orphan*/  convert_flags (TYPE_1__*,int /*<<< orphan*/ ,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  default_encoded_callback ; 
 int /*<<< orphan*/  default_raw_video_callback ; 
 int /*<<< orphan*/  do_output_signal (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  interleave_packets ; 
 int /*<<< orphan*/  obs_encoder_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  obs_output_cleanup_delay (TYPE_1__*) ; 
 int /*<<< orphan*/  obs_service_deactivate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_event_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_delay ; 
 int /*<<< orphan*/  stop_audio_encoders (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_raw_audio (TYPE_1__*) ; 
 int /*<<< orphan*/  stop_raw_video (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void *end_data_capture_thread(void *data)
{
	bool encoded, has_video, has_audio, has_service;
	encoded_callback_t encoded_callback;
	obs_output_t *output = data;

	convert_flags(output, 0, &encoded, &has_video, &has_audio,
		      &has_service);

	if (encoded) {
		if (output->active_delay_ns)
			encoded_callback = process_delay;
		else
			encoded_callback = (has_video && has_audio)
						   ? interleave_packets
						   : default_encoded_callback;

		if (has_video)
			obs_encoder_stop(output->video_encoder,
					 encoded_callback, output);
		if (has_audio)
			stop_audio_encoders(output, encoded_callback);
	} else {
		if (has_video)
			stop_raw_video(output->video,
				       default_raw_video_callback, output);
		if (has_audio)
			stop_raw_audio(output);
	}

	if (has_service)
		obs_service_deactivate(output->service, false);

	if (output->active_delay_ns)
		obs_output_cleanup_delay(output);

	do_output_signal(output, "deactivate");
	os_atomic_set_bool(&output->active, false);
	os_event_signal(output->stopping_event);
	os_atomic_set_bool(&output->end_data_capture_thread_active, false);

	return NULL;
}