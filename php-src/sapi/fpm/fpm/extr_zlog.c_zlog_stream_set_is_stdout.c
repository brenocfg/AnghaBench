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
struct zlog_stream {int is_stdout; } ;

/* Variables and functions */

void zlog_stream_set_is_stdout(struct zlog_stream *stream, zlog_bool is_stdout) /* {{{ */
{
	stream->is_stdout = is_stdout ? 1 : 0;
}