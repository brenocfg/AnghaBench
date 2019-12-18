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
typedef  int /*<<< orphan*/  uint8_t ;
struct ffmpeg_muxer {int /*<<< orphan*/  capturing; int /*<<< orphan*/  output; int /*<<< orphan*/  pipe; } ;
typedef  int /*<<< orphan*/  error ;

/* Variables and functions */
#define  FFM_UNSUPPORTED 128 
 int OBS_OUTPUT_ERROR ; 
 int OBS_OUTPUT_UNSUPPORTED ; 
 int deactivate (struct ffmpeg_muxer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_output_set_last_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  obs_output_signal_stop (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 size_t os_process_pipe_read_err (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

__attribute__((used)) static void signal_failure(struct ffmpeg_muxer *stream)
{
	char error[1024];
	int ret;
	int code;

	size_t len;

	len = os_process_pipe_read_err(stream->pipe, (uint8_t *)error,
				       sizeof(error) - 1);

	if (len > 0) {
		error[len] = 0;
		warn("ffmpeg-mux: %s", error);
		obs_output_set_last_error(stream->output, error);
	}

	ret = deactivate(stream, 0);

	switch (ret) {
	case FFM_UNSUPPORTED:
		code = OBS_OUTPUT_UNSUPPORTED;
		break;
	default:
		code = OBS_OUTPUT_ERROR;
	}

	obs_output_signal_stop(stream->output, code);
	os_atomic_set_bool(&stream->capturing, false);
}