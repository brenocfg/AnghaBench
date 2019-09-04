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
struct zlog_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  zlog_stream_init_internal (struct zlog_stream*,int,int,int /*<<< orphan*/ ) ; 

void zlog_stream_init(struct zlog_stream *stream, int flags) /* {{{ */
{
	zlog_stream_init_internal(stream, flags, 1024, 0);
}