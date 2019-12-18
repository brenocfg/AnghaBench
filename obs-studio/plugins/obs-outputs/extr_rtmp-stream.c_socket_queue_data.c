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
struct rtmp_stream {scalar_t__ write_buf_len; scalar_t__ write_buf_size; scalar_t__ write_buf; int /*<<< orphan*/  buffer_has_data_event; int /*<<< orphan*/  write_buf_mutex; int /*<<< orphan*/  buffer_space_available_event; int /*<<< orphan*/  rtmp; } ;
typedef  int /*<<< orphan*/  RTMPSockBuf ;

/* Variables and functions */
 int /*<<< orphan*/  RTMP_IsConnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int) ; 
 int /*<<< orphan*/  os_event_signal (int /*<<< orphan*/ ) ; 
 scalar_t__ os_event_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int socket_queue_data(RTMPSockBuf *sb, const char *data, int len,
			     void *arg)
{
	UNUSED_PARAMETER(sb);

	struct rtmp_stream *stream = arg;

retry_send:

	if (!RTMP_IsConnected(&stream->rtmp))
		return 0;

	pthread_mutex_lock(&stream->write_buf_mutex);

	if (stream->write_buf_len + len > stream->write_buf_size) {

		pthread_mutex_unlock(&stream->write_buf_mutex);

		if (os_event_wait(stream->buffer_space_available_event)) {
			return 0;
		}

		goto retry_send;
	}

	memcpy(stream->write_buf + stream->write_buf_len, data, len);
	stream->write_buf_len += len;

	pthread_mutex_unlock(&stream->write_buf_mutex);

	os_event_signal(stream->buffer_has_data_event);

	return len;
}