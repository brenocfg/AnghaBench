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
struct ftl_stream {int /*<<< orphan*/  output; int /*<<< orphan*/  active; int /*<<< orphan*/  send_thread; } ;

/* Variables and functions */
 int OBS_OUTPUT_ERROR ; 
 int OBS_OUTPUT_SUCCESS ; 
 int /*<<< orphan*/  obs_output_begin_data_capture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ftl_stream*) ; 
 int /*<<< orphan*/  reset_semaphore (struct ftl_stream*) ; 
 int /*<<< orphan*/  send_thread ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int init_send(struct ftl_stream *stream)
{
	int ret;

	reset_semaphore(stream);

	ret = pthread_create(&stream->send_thread, NULL, send_thread, stream);
	if (ret != 0) {
		warn("Failed to create send thread");
		return OBS_OUTPUT_ERROR;
	}

	os_atomic_set_bool(&stream->active, true);

	obs_output_begin_data_capture(stream->output, 0);

	return OBS_OUTPUT_SUCCESS;
}