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
struct ring_buffer {TYPE_1__** buffers; } ;
struct TYPE_2__ {size_t nr_pages; } ;

/* Variables and functions */

size_t ring_buffer_nr_pages(struct ring_buffer *buffer, int cpu)
{
	return buffer->buffers[cpu]->nr_pages;
}