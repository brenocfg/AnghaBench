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
struct TYPE_2__ {int connect_time_ms; } ;
struct rtmp_stream {TYPE_1__ rtmp; } ;

/* Variables and functions */

__attribute__((used)) static int rtmp_stream_connect_time(void *data)
{
	struct rtmp_stream *stream = data;
	return stream->rtmp.connect_time_ms;
}