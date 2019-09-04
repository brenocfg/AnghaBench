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
struct TYPE_3__ {int /*<<< orphan*/  sb_socket; } ;
struct TYPE_4__ {int m_bCustomSend; struct rtmp_stream* m_customSendParam; int /*<<< orphan*/  m_customSendFunc; int /*<<< orphan*/  last_error_code; TYPE_1__ m_sb; } ;
struct rtmp_stream {int low_latency_mode; int write_buf_size; int socket_thread_active; int /*<<< orphan*/ * output; int /*<<< orphan*/  active; TYPE_2__ rtmp; int /*<<< orphan*/  write_buf; int /*<<< orphan*/  send_thread_signaled_exit; scalar_t__ new_socket_loop; int /*<<< orphan*/  send_thread; } ;
typedef  int /*<<< orphan*/  obs_output_t ;
typedef  int /*<<< orphan*/  obs_encoder_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIONBIO ; 
 int OBS_OUTPUT_DISCONNECTED ; 
 int OBS_OUTPUT_ERROR ; 
 int OBS_OUTPUT_SUCCESS ; 
 int /*<<< orphan*/  RTMP_Close (TYPE_2__*) ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bmalloc (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  info (char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_encoder_get_settings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_output_begin_data_capture (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_output_get_audio_encoder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_output_get_video_encoder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_event_reset (int /*<<< orphan*/ ) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rtmp_stream*) ; 
 int /*<<< orphan*/  reset_semaphore (struct rtmp_stream*) ; 
 int /*<<< orphan*/  send_meta_data (struct rtmp_stream*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  send_thread ; 
 int /*<<< orphan*/  set_output_error (struct rtmp_stream*) ; 
 int /*<<< orphan*/  socket_queue_data ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int init_send(struct rtmp_stream *stream)
{
	int ret;
	size_t idx = 0;
	bool next = true;

#if defined(_WIN32)
	adjust_sndbuf_size(stream, MIN_SENDBUF_SIZE);
#endif

	reset_semaphore(stream);

	ret = pthread_create(&stream->send_thread, NULL, send_thread, stream);
	if (ret != 0) {
		RTMP_Close(&stream->rtmp);
		warn("Failed to create send thread");
		return OBS_OUTPUT_ERROR;
	}

	if (stream->new_socket_loop) {
		int one = 1;
#ifdef _WIN32
		if (ioctlsocket(stream->rtmp.m_sb.sb_socket, FIONBIO, &one)) {
			stream->rtmp.last_error_code = WSAGetLastError();
#else
		if (ioctl(stream->rtmp.m_sb.sb_socket, FIONBIO, &one)) {
			stream->rtmp.last_error_code = errno;
#endif
			warn("Failed to set non-blocking socket");
			return OBS_OUTPUT_ERROR;
		}

		os_event_reset(stream->send_thread_signaled_exit);

		info("New socket loop enabled by user");
		if (stream->low_latency_mode)
			info("Low latency mode enabled by user");

		if (stream->write_buf)
			bfree(stream->write_buf);

		int total_bitrate = 0;
		obs_output_t  *context  = stream->output;

		obs_encoder_t *vencoder = obs_output_get_video_encoder(context);
		if (vencoder) {
			obs_data_t *params = obs_encoder_get_settings(vencoder);
			if (params) {
				int bitrate = obs_data_get_int(params, "bitrate");
				if (!bitrate) {
					warn ("Video encoder didn't return a "
						"valid bitrate, new network "
						"code may function poorly. "
						"Low latency mode disabled.");
					stream->low_latency_mode = false;
					bitrate = 10000;
				}
				total_bitrate += bitrate;
				obs_data_release(params);
			}
		}

		obs_encoder_t *aencoder = obs_output_get_audio_encoder(context, 0);
		if (aencoder) {
			obs_data_t *params = obs_encoder_get_settings(aencoder);
			if (params) {
				int bitrate = obs_data_get_int(params, "bitrate");
				if (!bitrate)
					bitrate = 160;
				total_bitrate += bitrate;
				obs_data_release(params);
			}
		}

		// to bytes/sec
		int ideal_buffer_size = total_bitrate * 128;

		if (ideal_buffer_size < 131072)
			ideal_buffer_size = 131072;

		stream->write_buf_size = ideal_buffer_size;
		stream->write_buf = bmalloc(ideal_buffer_size);

#ifdef _WIN32
		ret = pthread_create(&stream->socket_thread, NULL,
				socket_thread_windows, stream);
#else
		warn("New socket loop not supported on this platform");
		return OBS_OUTPUT_ERROR;
#endif

		if (ret != 0) {
			RTMP_Close(&stream->rtmp);
			warn("Failed to create socket thread");
			return OBS_OUTPUT_ERROR;
		}

		stream->socket_thread_active = true;
		stream->rtmp.m_bCustomSend = true;
		stream->rtmp.m_customSendFunc = socket_queue_data;
		stream->rtmp.m_customSendParam = stream;
	}

	os_atomic_set_bool(&stream->active, true);
	while (next) {
		if (!send_meta_data(stream, idx++, &next)) {
			warn("Disconnected while attempting to connect to "
			     "server.");
			set_output_error(stream);
			return OBS_OUTPUT_DISCONNECTED;
		}
	}
	obs_output_begin_data_capture(stream->output, 0);

	return OBS_OUTPUT_SUCCESS;
}