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
typedef  scalar_t__ u32 ;
struct bpf_queue_stack {scalar_t__ head; scalar_t__ size; scalar_t__ tail; } ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool queue_stack_map_is_full(struct bpf_queue_stack *qs)
{
	u32 head = qs->head + 1;

	if (unlikely(head >= qs->size))
		head = 0;

	return head == qs->tail;
}