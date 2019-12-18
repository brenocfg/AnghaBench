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
struct ftl_stream {int /*<<< orphan*/  connect_thread; int /*<<< orphan*/  connecting; scalar_t__ frames_sent; int /*<<< orphan*/  output; } ;
typedef  int /*<<< orphan*/  obs_encoder_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  connect_thread ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_set_int (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_encoder_get_settings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_output_can_begin_data_capture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_output_get_video_encoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_output_initialize_encoders (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ftl_stream*) ; 

__attribute__((used)) static bool ftl_stream_start(void *data)
{
	struct ftl_stream *stream = data;

	info("ftl_stream_start");

	// Mixer doesn't support bframes. So force them off.
	obs_encoder_t *video_encoder =
		obs_output_get_video_encoder(stream->output);
	obs_data_t *video_settings = obs_encoder_get_settings(video_encoder);
	obs_data_set_int(video_settings, "bf", 0);
	obs_data_release(video_settings);

	if (!obs_output_can_begin_data_capture(stream->output, 0)) {
		return false;
	}
	if (!obs_output_initialize_encoders(stream->output, 0)) {
		return false;
	}

	stream->frames_sent = 0;
	os_atomic_set_bool(&stream->connecting, true);

	return pthread_create(&stream->connect_thread, NULL, connect_thread,
			      stream) == 0;
}