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
struct flv_output {int sent_headers; int got_first_video; int /*<<< orphan*/  mutex; int /*<<< orphan*/  start_dts_offset; scalar_t__ stop_ts; } ;
struct encoder_packet {scalar_t__ sys_dts_usec; scalar_t__ type; int /*<<< orphan*/  dts; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ OBS_ENCODER_VIDEO ; 
 int /*<<< orphan*/  OBS_OUTPUT_ENCODE_ERROR ; 
 int /*<<< orphan*/  active (struct flv_output*) ; 
 int /*<<< orphan*/  flv_output_actual_stop (struct flv_output*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ms_time (struct encoder_packet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_encoder_packet_release (struct encoder_packet*) ; 
 int /*<<< orphan*/  obs_parse_avc_packet (struct encoder_packet*,struct encoder_packet*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stopping (struct flv_output*) ; 
 int /*<<< orphan*/  write_headers (struct flv_output*) ; 
 int /*<<< orphan*/  write_packet (struct flv_output*,struct encoder_packet*,int) ; 

__attribute__((used)) static void flv_output_data(void *data, struct encoder_packet *packet)
{
	struct flv_output *stream = data;
	struct encoder_packet parsed_packet;

	pthread_mutex_lock(&stream->mutex);

	if (!active(stream))
		goto unlock;

	if (!packet) {
		flv_output_actual_stop(stream, OBS_OUTPUT_ENCODE_ERROR);
		goto unlock;
	}

	if (stopping(stream)) {
		if (packet->sys_dts_usec >= (int64_t)stream->stop_ts) {
			flv_output_actual_stop(stream, 0);
			goto unlock;
		}
	}

	if (!stream->sent_headers) {
		write_headers(stream);
		stream->sent_headers = true;
	}

	if (packet->type == OBS_ENCODER_VIDEO) {
		if (!stream->got_first_video) {
			stream->start_dts_offset =
				get_ms_time(packet, packet->dts);
			stream->got_first_video = true;
		}

		obs_parse_avc_packet(&parsed_packet, packet);
		write_packet(stream, &parsed_packet, false);
		obs_encoder_packet_release(&parsed_packet);
	} else {
		write_packet(stream, packet, false);
	}

unlock:
	pthread_mutex_unlock(&stream->mutex);
}