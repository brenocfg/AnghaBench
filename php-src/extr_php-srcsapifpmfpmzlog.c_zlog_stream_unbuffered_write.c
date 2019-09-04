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
struct zlog_stream {size_t len; size_t msg_suffix_len; size_t msg_quote; char const* msg_suffix; int full; scalar_t__ wrap; int /*<<< orphan*/  line; int /*<<< orphan*/  function; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 size_t zlog_limit ; 
 int /*<<< orphan*/  zlog_stream_direct_write (struct zlog_stream*,char const*,size_t) ; 
 scalar_t__ zlog_stream_direct_write_ex (struct zlog_stream*,char const*,size_t,char const*,size_t) ; 
 size_t zlog_stream_prefix_ex (struct zlog_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline ssize_t zlog_stream_unbuffered_write(
		struct zlog_stream *stream, const char *buf, size_t len) /* {{{ */
{
	const char *append;
	size_t append_len = 0, required_len, reserved_len;
	ssize_t written;

	if (stream->len == 0) {
		stream->len = zlog_stream_prefix_ex(stream, stream->function, stream->line);
	}

	/* msg_suffix_len and msg_quote are used only for wrapping */
	reserved_len = stream->len + stream->msg_suffix_len + stream->msg_quote;
	required_len = reserved_len + len;
	if (required_len >= zlog_limit) {
		if (stream->wrap) {
			size_t available_len;
			if (required_len == zlog_limit) {
				append = NULL;
				append_len = 0;
			} else {
				append = "\n";
				append_len = 1;
			}
			available_len = zlog_limit - reserved_len - 1;
			zlog_stream_direct_write(stream, buf, available_len);
			if (append != NULL) {
				if (stream->msg_quote) {
					zlog_stream_direct_write(stream, "\"", 1);
				}
				if (stream->msg_suffix) {
					zlog_stream_direct_write(stream, stream->msg_suffix, stream->msg_suffix_len);
				}
				zlog_stream_direct_write(stream, append, append_len);
			}
			stream->len = 0;
			written = zlog_stream_unbuffered_write(
					stream, buf + available_len, len - available_len);
			if (written > 0) {
				return available_len + written;
			}

			return written;
		}
		/* this would be used in case of an option for disabling wrapping in direct write */
		stream->full = 1;
		if (required_len == zlog_limit) {
			append = NULL;
		} else {
			append = "...";
			append_len = sizeof("...") - 1;
			len = zlog_limit - stream->len - append_len;
		}
	}

	written = zlog_stream_direct_write_ex(stream, buf, len, append, append_len);
	if (written > 0) {
		/* currently written will be always len as the write is blocking
		 * - this should be address if we change to non-blocking write */
		stream->len += written;
	}

	return written;
}