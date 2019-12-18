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
struct zlog_stream {int wrap; } ;

/* Variables and functions */
 int /*<<< orphan*/  zlog_stream_init_internal (struct zlog_stream*,int,int,int) ; 

void zlog_stream_init_ex(struct zlog_stream *stream, int flags, int fd) /* {{{ */
{
	zlog_stream_init_internal(stream, flags, 1024, fd);
	stream->wrap = 1;
}