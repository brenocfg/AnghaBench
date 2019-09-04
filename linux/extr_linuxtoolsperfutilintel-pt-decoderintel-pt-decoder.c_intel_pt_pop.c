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
typedef  int /*<<< orphan*/  uint64_t ;
struct intel_pt_stack {size_t pos; TYPE_1__* blk; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ip; } ;

/* Variables and functions */
 size_t INTEL_PT_BLK_SIZE ; 
 int /*<<< orphan*/  intel_pt_pop_blk (struct intel_pt_stack*) ; 

__attribute__((used)) static uint64_t intel_pt_pop(struct intel_pt_stack *stack)
{
	if (!stack->pos) {
		if (!stack->blk)
			return 0;
		intel_pt_pop_blk(stack);
		if (!stack->blk)
			return 0;
		stack->pos = INTEL_PT_BLK_SIZE;
	}
	return stack->blk->ip[--stack->pos];
}