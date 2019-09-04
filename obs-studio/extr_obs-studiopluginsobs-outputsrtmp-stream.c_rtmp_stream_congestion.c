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
struct rtmp_stream {scalar_t__ min_priority; float congestion; scalar_t__ write_buf_size; scalar_t__ write_buf_len; scalar_t__ new_socket_loop; } ;

/* Variables and functions */

__attribute__((used)) static float rtmp_stream_congestion(void *data)
{
	struct rtmp_stream *stream = data;

	if (stream->new_socket_loop)
		return (float)stream->write_buf_len /
			(float)stream->write_buf_size;
	else
		return stream->min_priority > 0 ? 1.0f : stream->congestion;
}