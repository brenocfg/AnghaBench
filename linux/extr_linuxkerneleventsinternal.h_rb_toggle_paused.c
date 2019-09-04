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
struct ring_buffer {int paused; scalar_t__ nr_pages; } ;

/* Variables and functions */

__attribute__((used)) static inline void rb_toggle_paused(struct ring_buffer *rb, bool pause)
{
	if (!pause && rb->nr_pages)
		rb->paused = 0;
	else
		rb->paused = 1;
}