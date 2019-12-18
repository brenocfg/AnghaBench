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
struct TYPE_2__ {int /*<<< orphan*/  array; } ;
struct ffmpeg_muxer {int /*<<< orphan*/  stopping; int /*<<< orphan*/  output; TYPE_1__ path; int /*<<< orphan*/  sent_headers; int /*<<< orphan*/  active; int /*<<< orphan*/ * pipe; } ;

/* Variables and functions */
 scalar_t__ active (struct ffmpeg_muxer*) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_output_end_data_capture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_output_signal_stop (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int os_process_pipe_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ stopping (struct ffmpeg_muxer*) ; 

__attribute__((used)) static int deactivate(struct ffmpeg_muxer *stream, int code)
{
	int ret = -1;

	if (active(stream)) {
		ret = os_process_pipe_destroy(stream->pipe);
		stream->pipe = NULL;

		os_atomic_set_bool(&stream->active, false);
		os_atomic_set_bool(&stream->sent_headers, false);

		info("Output of file '%s' stopped", stream->path.array);
	}

	if (code) {
		obs_output_signal_stop(stream->output, code);
	} else if (stopping(stream)) {
		obs_output_end_data_capture(stream->output);
	}

	os_atomic_set_bool(&stream->stopping, false);
	return ret;
}