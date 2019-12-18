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
struct TYPE_2__ {int size; char* data; } ;
struct zlog_stream {int len; TYPE_1__ buf; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  zlog_stream_buf_alloc_ex (struct zlog_stream*,int) ; 

__attribute__((used)) static inline ssize_t zlog_stream_buf_copy_char(struct zlog_stream *stream, char c) /* {{{ */
{
	if (stream->buf.size - stream->len < 1 && !zlog_stream_buf_alloc_ex(stream, 1)) {
		return -1;
	}

	stream->buf.data[stream->len++] = c;

	return 1;
}