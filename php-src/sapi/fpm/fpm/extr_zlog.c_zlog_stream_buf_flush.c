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
struct TYPE_2__ {scalar_t__ data; } ;
struct zlog_stream {int flags; scalar_t__ len; TYPE_1__ buf; scalar_t__ prefix_len; scalar_t__ use_syslog; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int ZLOG_LEVEL_MASK ; 
 int /*<<< orphan*/  external_logger (int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  php_syslog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/ * syslog_priorities ; 
 size_t zlog_level ; 
 int /*<<< orphan*/  zlog_stream_buf_copy_char (struct zlog_stream*,char) ; 
 int /*<<< orphan*/  zlog_stream_direct_write (struct zlog_stream*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static ssize_t zlog_stream_buf_flush(struct zlog_stream *stream) /* {{{ */
{
	ssize_t written;

#ifdef HAVE_SYSLOG_H
	if (stream->use_syslog) {
		zlog_stream_buf_copy_char(stream, '\0');
		php_syslog(syslog_priorities[zlog_level], "%s", stream->buf.data);
		--stream->len;
	}
#endif

	if (external_logger != NULL) {
		external_logger(stream->flags & ZLOG_LEVEL_MASK,
				stream->buf.data + stream->prefix_len, stream->len - stream->prefix_len);
	}
	zlog_stream_buf_copy_char(stream, '\n');
	written = zlog_stream_direct_write(stream, stream->buf.data, stream->len);
	stream->len = 0;

	return written;
}