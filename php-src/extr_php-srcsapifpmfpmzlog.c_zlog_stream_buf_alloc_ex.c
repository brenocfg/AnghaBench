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
struct TYPE_2__ {size_t size; char* data; } ;
struct zlog_stream {size_t buf_init_size; TYPE_1__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (size_t,size_t) ; 
 size_t MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* malloc (size_t) ; 
 char* realloc (char*,size_t) ; 
 int /*<<< orphan*/  zlog_limit ; 

__attribute__((used)) static zlog_bool zlog_stream_buf_alloc_ex(struct zlog_stream *stream, size_t needed)  /* {{{ */
{
	char *buf;
	size_t size = stream->buf.size ?: stream->buf_init_size;

	if (stream->buf.data) {
		size = MIN(zlog_limit, MAX(size * 2, needed));
		buf = realloc(stream->buf.data, size);
	} else {
		size = MIN(zlog_limit, MAX(size, needed));
		buf = malloc(size);
	}

	if (buf == NULL) {
		return 0;
	}

	stream->buf.data = buf;
	stream->buf.size = size;

	return 1;
}