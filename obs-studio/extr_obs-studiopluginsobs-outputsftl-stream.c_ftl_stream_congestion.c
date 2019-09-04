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
struct ftl_stream {scalar_t__ min_priority; float congestion; } ;

/* Variables and functions */

__attribute__((used)) static float ftl_stream_congestion(void *data)
{
	struct ftl_stream *stream = data;
	return stream->min_priority > 0 ? 1.0f : stream->congestion;
}