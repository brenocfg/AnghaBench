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
struct zlog_stream {int msg_quote; scalar_t__ decorate; } ;

/* Variables and functions */

void zlog_stream_set_msg_quoting(struct zlog_stream *stream, zlog_bool quote) /* {{{ */
{
	stream->msg_quote = quote && stream->decorate ? 1 : 0;
}