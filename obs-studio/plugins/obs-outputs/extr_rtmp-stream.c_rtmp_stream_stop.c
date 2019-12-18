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
typedef  scalar_t__ uint64_t ;
struct rtmp_stream {int /*<<< orphan*/  output; int /*<<< orphan*/  send_sem; scalar_t__ stop_ts; int /*<<< orphan*/  stop_event; scalar_t__ max_shutdown_time_sec; scalar_t__ shutdown_timeout_ts; int /*<<< orphan*/  connect_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_OUTPUT_SUCCESS ; 
 scalar_t__ active (struct rtmp_stream*) ; 
 scalar_t__ connecting (struct rtmp_stream*) ; 
 int /*<<< orphan*/  obs_output_signal_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_event_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_sem_post (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stopping (struct rtmp_stream*) ; 

__attribute__((used)) static void rtmp_stream_stop(void *data, uint64_t ts)
{
	struct rtmp_stream *stream = data;

	if (stopping(stream) && ts != 0)
		return;

	if (connecting(stream))
		pthread_join(stream->connect_thread, NULL);

	stream->stop_ts = ts / 1000ULL;

	if (ts)
		stream->shutdown_timeout_ts =
			ts +
			(uint64_t)stream->max_shutdown_time_sec * 1000000000ULL;

	if (active(stream)) {
		os_event_signal(stream->stop_event);
		if (stream->stop_ts == 0)
			os_sem_post(stream->send_sem);
	} else {
		obs_output_signal_stop(stream->output, OBS_OUTPUT_SUCCESS);
	}
}