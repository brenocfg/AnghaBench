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
struct rtmp_stream {int /*<<< orphan*/  connect_thread; int /*<<< orphan*/  connecting; int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int /*<<< orphan*/  connect_thread ; 
 int /*<<< orphan*/  obs_output_can_begin_data_capture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_output_initialize_encoders (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rtmp_stream*) ; 

__attribute__((used)) static bool rtmp_stream_start(void *data)
{
	struct rtmp_stream *stream = data;

	if (!obs_output_can_begin_data_capture(stream->output, 0))
		return false;
	if (!obs_output_initialize_encoders(stream->output, 0))
		return false;

	os_atomic_set_bool(&stream->connecting, true);
	return pthread_create(&stream->connect_thread, NULL, connect_thread,
			      stream) == 0;
}