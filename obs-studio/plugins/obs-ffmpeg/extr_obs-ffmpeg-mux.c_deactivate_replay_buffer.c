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
struct ffmpeg_muxer {int /*<<< orphan*/  stopping; int /*<<< orphan*/  sent_headers; int /*<<< orphan*/  active; int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int /*<<< orphan*/  obs_output_end_data_capture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_output_signal_stop (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  replay_buffer_clear (struct ffmpeg_muxer*) ; 
 scalar_t__ stopping (struct ffmpeg_muxer*) ; 

__attribute__((used)) static void deactivate_replay_buffer(struct ffmpeg_muxer *stream, int code)
{
	if (code) {
		obs_output_signal_stop(stream->output, code);
	} else if (stopping(stream)) {
		obs_output_end_data_capture(stream->output);
	}

	os_atomic_set_bool(&stream->active, false);
	os_atomic_set_bool(&stream->sent_headers, false);
	os_atomic_set_bool(&stream->stopping, false);
	replay_buffer_clear(stream);
}