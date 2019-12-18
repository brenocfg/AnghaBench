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
struct rtmp_stream {struct rtmp_stream* write_buf; int /*<<< orphan*/  write_buf_mutex; int /*<<< orphan*/  send_thread_signaled_exit; int /*<<< orphan*/  socket_available_event; int /*<<< orphan*/  buffer_has_data_event; int /*<<< orphan*/  buffer_space_available_event; int /*<<< orphan*/  dbr_mutex; int /*<<< orphan*/  dbr_frames; int /*<<< orphan*/  droptest_info; int /*<<< orphan*/  packets; int /*<<< orphan*/  packets_mutex; int /*<<< orphan*/  send_sem; int /*<<< orphan*/  stop_event; int /*<<< orphan*/  bind_ip; int /*<<< orphan*/  encoder_name; int /*<<< orphan*/  password; int /*<<< orphan*/  username; int /*<<< orphan*/  key; int /*<<< orphan*/  path; int /*<<< orphan*/  send_thread; int /*<<< orphan*/  output; scalar_t__ stop_ts; int /*<<< orphan*/  connect_thread; scalar_t__ connecting; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTMP_TLS_Free () ; 
 scalar_t__ active (struct rtmp_stream*) ; 
 int /*<<< orphan*/  bfree (struct rtmp_stream*) ; 
 int /*<<< orphan*/  circlebuf_free (int /*<<< orphan*/ *) ; 
 scalar_t__ connecting (struct rtmp_stream*) ; 
 int /*<<< orphan*/  dstr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_packets (struct rtmp_stream*) ; 
 int /*<<< orphan*/  obs_output_end_data_capture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_event_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_event_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_sem_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_sem_post (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ stopping (struct rtmp_stream*) ; 

__attribute__((used)) static void rtmp_stream_destroy(void *data)
{
	struct rtmp_stream *stream = data;

	if (stopping(stream) && !connecting(stream)) {
		pthread_join(stream->send_thread, NULL);

	} else if (connecting(stream) || active(stream)) {
		if (stream->connecting)
			pthread_join(stream->connect_thread, NULL);

		stream->stop_ts = 0;
		os_event_signal(stream->stop_event);

		if (active(stream)) {
			os_sem_post(stream->send_sem);
			obs_output_end_data_capture(stream->output);
			pthread_join(stream->send_thread, NULL);
		}
	}

	RTMP_TLS_Free();
	free_packets(stream);
	dstr_free(&stream->path);
	dstr_free(&stream->key);
	dstr_free(&stream->username);
	dstr_free(&stream->password);
	dstr_free(&stream->encoder_name);
	dstr_free(&stream->bind_ip);
	os_event_destroy(stream->stop_event);
	os_sem_destroy(stream->send_sem);
	pthread_mutex_destroy(&stream->packets_mutex);
	circlebuf_free(&stream->packets);
#ifdef TEST_FRAMEDROPS
	circlebuf_free(&stream->droptest_info);
#endif
	circlebuf_free(&stream->dbr_frames);
	pthread_mutex_destroy(&stream->dbr_mutex);

	os_event_destroy(stream->buffer_space_available_event);
	os_event_destroy(stream->buffer_has_data_event);
	os_event_destroy(stream->socket_available_event);
	os_event_destroy(stream->send_thread_signaled_exit);
	pthread_mutex_destroy(&stream->write_buf_mutex);

	if (stream->write_buf)
		bfree(stream->write_buf);
	bfree(stream);
}