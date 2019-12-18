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
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct ffmpeg_muxer {scalar_t__ stop_ts; scalar_t__ save_ts; int mux_thread_joinable; int /*<<< orphan*/  mux_thread; int /*<<< orphan*/  muxing; int /*<<< orphan*/  keyframes; TYPE_1__ packets; int /*<<< orphan*/  cur_size; int /*<<< orphan*/  cur_time; } ;
struct encoder_packet {scalar_t__ sys_dts_usec; scalar_t__ type; scalar_t__ keyframe; scalar_t__ size; int /*<<< orphan*/  dts_usec; } ;

/* Variables and functions */
 scalar_t__ OBS_ENCODER_VIDEO ; 
 int /*<<< orphan*/  OBS_OUTPUT_ENCODE_ERROR ; 
 int /*<<< orphan*/  active (struct ffmpeg_muxer*) ; 
 int /*<<< orphan*/  circlebuf_push_back (TYPE_1__*,struct encoder_packet*,int) ; 
 int /*<<< orphan*/  deactivate_replay_buffer (struct ffmpeg_muxer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_encoder_packet_ref (struct encoder_packet*,struct encoder_packet*) ; 
 scalar_t__ os_atomic_load_bool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  replay_buffer_purge (struct ffmpeg_muxer*,struct encoder_packet*) ; 
 int /*<<< orphan*/  replay_buffer_save (struct ffmpeg_muxer*) ; 
 scalar_t__ stopping (struct ffmpeg_muxer*) ; 

__attribute__((used)) static void replay_buffer_data(void *data, struct encoder_packet *packet)
{
	struct ffmpeg_muxer *stream = data;
	struct encoder_packet pkt;

	if (!active(stream))
		return;

	/* encoder failure */
	if (!packet) {
		deactivate_replay_buffer(stream, OBS_OUTPUT_ENCODE_ERROR);
		return;
	}

	if (stopping(stream)) {
		if (packet->sys_dts_usec >= stream->stop_ts) {
			deactivate_replay_buffer(stream, 0);
			return;
		}
	}

	obs_encoder_packet_ref(&pkt, packet);
	replay_buffer_purge(stream, &pkt);

	if (!stream->packets.size)
		stream->cur_time = pkt.dts_usec;
	stream->cur_size += pkt.size;

	circlebuf_push_back(&stream->packets, packet, sizeof(*packet));

	if (packet->type == OBS_ENCODER_VIDEO && packet->keyframe)
		stream->keyframes++;

	if (stream->save_ts && packet->sys_dts_usec >= stream->save_ts) {
		if (os_atomic_load_bool(&stream->muxing))
			return;

		if (stream->mux_thread_joinable) {
			pthread_join(stream->mux_thread, NULL);
			stream->mux_thread_joinable = false;
		}

		stream->save_ts = 0;
		replay_buffer_save(stream);
	}
}