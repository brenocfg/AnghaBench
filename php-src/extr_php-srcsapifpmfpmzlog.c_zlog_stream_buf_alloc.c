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
typedef  int zlog_bool ;
struct TYPE_2__ {scalar_t__ size; scalar_t__ data; } ;
struct zlog_stream {int /*<<< orphan*/  buf_init_size; TYPE_1__ buf; } ;

/* Variables and functions */
 scalar_t__ MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlog_limit ; 
 int zlog_stream_buf_alloc_ex (struct zlog_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) inline static zlog_bool zlog_stream_buf_alloc(struct zlog_stream *stream)  /* {{{ */
{
	/* if there is enough space in the buffer, we do not need to reallocate */
	if (stream->buf.data && stream->buf.size >= MIN(zlog_limit, stream->buf_init_size)) {
		return 1;
	}
	return zlog_stream_buf_alloc_ex(stream, 0);
}