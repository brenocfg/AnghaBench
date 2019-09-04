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
struct ftl_stream {int /*<<< orphan*/  packets; int /*<<< orphan*/  packets_mutex; int /*<<< orphan*/  send_sem; int /*<<< orphan*/  stop_event; int /*<<< orphan*/  bind_ip; int /*<<< orphan*/  encoder_name; int /*<<< orphan*/  password; int /*<<< orphan*/  username; int /*<<< orphan*/  path; int /*<<< orphan*/  ftl_handle; int /*<<< orphan*/  send_thread; int /*<<< orphan*/  output; scalar_t__ stop_ts; int /*<<< orphan*/  connect_thread; int /*<<< orphan*/  status_thread; scalar_t__ connecting; } ;
typedef  scalar_t__ ftl_status_t ;

/* Variables and functions */
 scalar_t__ FTL_SUCCESS ; 
 scalar_t__ active (struct ftl_stream*) ; 
 int /*<<< orphan*/  bfree (struct ftl_stream*) ; 
 int /*<<< orphan*/  circlebuf_free (int /*<<< orphan*/ *) ; 
 scalar_t__ connecting (struct ftl_stream*) ; 
 int /*<<< orphan*/  dstr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_packets (struct ftl_stream*) ; 
 scalar_t__ ftl_ingest_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  info (char*,...) ; 
 int /*<<< orphan*/  obs_output_end_data_capture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_event_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_event_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_sem_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_sem_post (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ stopping (struct ftl_stream*) ; 

__attribute__((used)) static void ftl_stream_destroy(void *data)
{
	struct ftl_stream *stream = data;
	ftl_status_t status_code;

	info("ftl_stream_destroy");

	if (stopping(stream) && !connecting(stream)) {
		pthread_join(stream->send_thread, NULL);

	} else if (connecting(stream) || active(stream)) {
		if (stream->connecting) {
			info("wait for connect_thread to terminate");
			pthread_join(stream->status_thread, NULL);
			pthread_join(stream->connect_thread, NULL);
			info("wait for connect_thread to terminate: done");
		}

		stream->stop_ts = 0;
		os_event_signal(stream->stop_event);

		if (active(stream)) {
			os_sem_post(stream->send_sem);
			obs_output_end_data_capture(stream->output);
			pthread_join(stream->send_thread, NULL);
		}
	}

	info("ingest destroy");

	status_code = ftl_ingest_destroy(&stream->ftl_handle);
	if (status_code != FTL_SUCCESS) {
		info("Failed to destroy from ingest %d", status_code);
	}

	if (stream) {
		free_packets(stream);
		dstr_free(&stream->path);
		dstr_free(&stream->username);
		dstr_free(&stream->password);
		dstr_free(&stream->encoder_name);
		dstr_free(&stream->bind_ip);
		os_event_destroy(stream->stop_event);
		os_sem_destroy(stream->send_sem);
		pthread_mutex_destroy(&stream->packets_mutex);
		circlebuf_free(&stream->packets);
		bfree(stream);
	}
}