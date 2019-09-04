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
typedef  scalar_t__ zlog_bool ;
struct zlog_stream {size_t msg_suffix_len; scalar_t__ len; size_t msg_final_suffix_len; int /*<<< orphan*/ * msg_final_suffix; scalar_t__ msg_quote; int /*<<< orphan*/  line; int /*<<< orphan*/  function; int /*<<< orphan*/ * msg_suffix; } ;

/* Variables and functions */
 scalar_t__ zlog_limit ; 
 int /*<<< orphan*/  zlog_stream_buf_copy_char (struct zlog_stream*,char) ; 
 int /*<<< orphan*/  zlog_stream_buf_copy_cstr (struct zlog_stream*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  zlog_stream_buf_flush (struct zlog_stream*) ; 
 int /*<<< orphan*/  zlog_stream_prefix_ex (struct zlog_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void zlog_stream_finish_buffer_suffix(struct zlog_stream *stream) /* {{{ */
{
	if (stream->msg_quote) {
		zlog_stream_buf_copy_char(stream, '"');
	}
	if (stream->msg_suffix != NULL) {
		zlog_stream_buf_copy_cstr(stream, stream->msg_suffix, stream->msg_suffix_len);
	}
	if (stream->msg_final_suffix != NULL) {
		if (stream->len + stream->msg_final_suffix_len >= zlog_limit) {
			zlog_bool quoting = stream->msg_quote;
			size_t final_suffix_wrap = stream->len + stream->msg_final_suffix_len + 1 - zlog_limit;
			zlog_stream_buf_copy_cstr(
					stream, stream->msg_final_suffix,
					stream->msg_final_suffix_len - final_suffix_wrap);
			zlog_stream_buf_copy_char(stream, '\n');
			zlog_stream_buf_flush(stream);
			stream->msg_quote = 0;
			zlog_stream_prefix_ex(stream, stream->function, stream->line);
			stream->msg_quote = quoting;
			zlog_stream_buf_copy_cstr(
					stream,
					stream->msg_final_suffix + (stream->msg_final_suffix_len - final_suffix_wrap),
					final_suffix_wrap);
			zlog_stream_buf_copy_char(stream, '\n');
		} else {
			zlog_stream_buf_copy_cstr(
					stream, stream->msg_final_suffix, stream->msg_final_suffix_len);
		}
	}
}