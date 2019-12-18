#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t num; struct encoder_packet* array; } ;
struct TYPE_3__ {int /*<<< orphan*/  array; } ;
struct ffmpeg_muxer {int /*<<< orphan*/  muxing; TYPE_2__ mux_packets; int /*<<< orphan*/ * pipe; TYPE_1__ path; } ;
struct encoder_packet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_free (TYPE_2__) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_encoder_packet_release (struct encoder_packet*) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_process_pipe_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_headers (struct ffmpeg_muxer*) ; 
 int /*<<< orphan*/  start_pipe (struct ffmpeg_muxer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  write_packet (struct ffmpeg_muxer*,struct encoder_packet*) ; 

__attribute__((used)) static void *replay_buffer_mux_thread(void *data)
{
	struct ffmpeg_muxer *stream = data;

	start_pipe(stream, stream->path.array);

	if (!stream->pipe) {
		warn("Failed to create process pipe");
		goto error;
	}

	if (!send_headers(stream)) {
		warn("Could not write headers for file '%s'",
		     stream->path.array);
		goto error;
	}

	for (size_t i = 0; i < stream->mux_packets.num; i++) {
		struct encoder_packet *pkt = &stream->mux_packets.array[i];
		write_packet(stream, pkt);
		obs_encoder_packet_release(pkt);
	}

	info("Wrote replay buffer to '%s'", stream->path.array);

error:
	os_process_pipe_destroy(stream->pipe);
	stream->pipe = NULL;
	da_free(stream->mux_packets);
	os_atomic_set_bool(&stream->muxing, false);
	return NULL;
}