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
struct ftl_stream {scalar_t__ dropped_frames; } ;

/* Variables and functions */

__attribute__((used)) static int ftl_stream_dropped_frames(void *data)
{
	struct ftl_stream *stream = data;
	return (int)stream->dropped_frames;
}