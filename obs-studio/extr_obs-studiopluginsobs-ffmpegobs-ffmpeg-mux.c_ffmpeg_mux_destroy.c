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
struct ffmpeg_muxer {int /*<<< orphan*/  path; int /*<<< orphan*/  pipe; int /*<<< orphan*/  mux_packets; int /*<<< orphan*/  mux_thread; scalar_t__ mux_thread_joinable; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct ffmpeg_muxer*) ; 
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_process_pipe_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  replay_buffer_clear (struct ffmpeg_muxer*) ; 

__attribute__((used)) static void ffmpeg_mux_destroy(void *data)
{
	struct ffmpeg_muxer *stream = data;

	replay_buffer_clear(stream);
	if (stream->mux_thread_joinable)
		pthread_join(stream->mux_thread, NULL);
	da_free(stream->mux_packets);

	os_process_pipe_destroy(stream->pipe);
	dstr_free(&stream->path);
	bfree(stream);
}