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
typedef  int /*<<< orphan*/  zlog_bool ;
struct zlog_stream {int finished; scalar_t__ len; scalar_t__ decorate; scalar_t__ use_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZLOG_TRUE ; 
 int /*<<< orphan*/  zlog_stream_buf_flush (struct zlog_stream*) ; 
 int /*<<< orphan*/  zlog_stream_direct_write (struct zlog_stream*,char*,int) ; 
 int /*<<< orphan*/  zlog_stream_finish_buffer_suffix (struct zlog_stream*) ; 
 int /*<<< orphan*/  zlog_stream_finish_direct_suffix (struct zlog_stream*) ; 

zlog_bool zlog_stream_finish(struct zlog_stream *stream) /* {{{ */
{
	if (stream->finished || stream->len == 0) {
		return ZLOG_TRUE;
	}

	if (stream->use_buffer) {
		if (stream->decorate) {
			zlog_stream_finish_buffer_suffix(stream);
		}
		zlog_stream_buf_flush(stream);
	} else {
		if (stream->decorate) {
			zlog_stream_finish_direct_suffix(stream);
		} else {
			zlog_stream_direct_write(stream, "\n", 1);
		}
	}
	stream->finished = 1;

	return ZLOG_TRUE;
}