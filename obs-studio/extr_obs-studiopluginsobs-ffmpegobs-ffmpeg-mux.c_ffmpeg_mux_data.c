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
struct ffmpeg_muxer {int sent_headers; scalar_t__ stop_ts; } ;
struct encoder_packet {scalar_t__ sys_dts_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  active (struct ffmpeg_muxer*) ; 
 int /*<<< orphan*/  deactivate (struct ffmpeg_muxer*) ; 
 int /*<<< orphan*/  send_headers (struct ffmpeg_muxer*) ; 
 scalar_t__ stopping (struct ffmpeg_muxer*) ; 
 int /*<<< orphan*/  write_packet (struct ffmpeg_muxer*,struct encoder_packet*) ; 

__attribute__((used)) static void ffmpeg_mux_data(void *data, struct encoder_packet *packet)
{
	struct ffmpeg_muxer *stream = data;

	if (!active(stream))
		return;

	if (!stream->sent_headers) {
		if (!send_headers(stream))
			return;

		stream->sent_headers = true;
	}

	if (stopping(stream)) {
		if (packet->sys_dts_usec >= stream->stop_ts) {
			deactivate(stream);
			return;
		}
	}

	write_packet(stream, packet);
}