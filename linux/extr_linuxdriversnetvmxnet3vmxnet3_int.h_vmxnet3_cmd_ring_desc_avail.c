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
struct vmxnet3_cmd_ring {scalar_t__ next2comp; scalar_t__ next2fill; int size; } ;

/* Variables and functions */

__attribute__((used)) static inline int
vmxnet3_cmd_ring_desc_avail(struct vmxnet3_cmd_ring *ring)
{
	return (ring->next2comp > ring->next2fill ? 0 : ring->size) +
		ring->next2comp - ring->next2fill - 1;
}