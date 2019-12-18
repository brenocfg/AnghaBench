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
struct zlog_stream {int child_pid; } ;

/* Variables and functions */

void zlog_stream_set_child_pid(struct zlog_stream *stream, int child_pid) /* {{{ */
{
	stream->child_pid = child_pid;
}