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
struct ordered_events {int copy_on_queue; } ;

/* Variables and functions */

__attribute__((used)) static inline
void ordered_events__set_copy_on_queue(struct ordered_events *oe, bool copy)
{
	oe->copy_on_queue = copy;
}