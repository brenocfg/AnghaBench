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
struct ring_buffer {int time_stamp_abs; } ;

/* Variables and functions */

void ring_buffer_set_time_stamp_abs(struct ring_buffer *buffer, bool abs)
{
	buffer->time_stamp_abs = abs;
}