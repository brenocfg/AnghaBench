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
struct rtmp_stream {int got_first_video; int /*<<< orphan*/  send_sem; int /*<<< orphan*/  packets_mutex; int /*<<< orphan*/  start_dts_offset; int /*<<< orphan*/  encode_error; } ;
struct encoder_packet {scalar_t__ type; int /*<<< orphan*/  dts; } ;

/* Variables and functions */
 scalar_t__ OBS_ENCODER_VIDEO ; 
 int /*<<< orphan*/  active (struct rtmp_stream*) ; 
 int add_packet (struct rtmp_stream*,struct encoder_packet*) ; 
 int add_video_packet (struct rtmp_stream*,struct encoder_packet*) ; 
 scalar_t__ disconnected (struct rtmp_stream*) ; 
 int /*<<< orphan*/  get_ms_time (struct encoder_packet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_encoder_packet_ref (struct encoder_packet*,struct encoder_packet*) ; 
 int /*<<< orphan*/  obs_encoder_packet_release (struct encoder_packet*) ; 
 int /*<<< orphan*/  obs_parse_avc_packet (struct encoder_packet*,struct encoder_packet*) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_sem_post (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtmp_stream_data(void *data, struct encoder_packet *packet)
{
	struct rtmp_stream *stream = data;
	struct encoder_packet new_packet;
	bool added_packet = false;

	if (disconnected(stream) || !active(stream))
		return;

	/* encoder fail */
	if (!packet) {
		os_atomic_set_bool(&stream->encode_error, true);
		os_sem_post(stream->send_sem);
		return;
	}

	if (packet->type == OBS_ENCODER_VIDEO) {
		if (!stream->got_first_video) {
			stream->start_dts_offset =
				get_ms_time(packet, packet->dts);
			stream->got_first_video = true;
		}

		obs_parse_avc_packet(&new_packet, packet);
	} else {
		obs_encoder_packet_ref(&new_packet, packet);
	}

	pthread_mutex_lock(&stream->packets_mutex);

	if (!disconnected(stream)) {
		added_packet = (packet->type == OBS_ENCODER_VIDEO)
				       ? add_video_packet(stream, &new_packet)
				       : add_packet(stream, &new_packet);
	}

	pthread_mutex_unlock(&stream->packets_mutex);

	if (added_packet)
		os_sem_post(stream->send_sem);
	else
		obs_encoder_packet_release(&new_packet);
}