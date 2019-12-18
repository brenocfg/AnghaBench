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
struct intel_pt_stack {scalar_t__ pos; TYPE_1__* blk; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ip; } ;

/* Variables and functions */
 scalar_t__ INTEL_PT_BLK_SIZE ; 
 int intel_pt_alloc_blk (struct intel_pt_stack*) ; 

__attribute__((used)) static int intel_pt_push(struct intel_pt_stack *stack, uint64_t ip)
{
	int err;

	if (!stack->blk || stack->pos == INTEL_PT_BLK_SIZE) {
		err = intel_pt_alloc_blk(stack);
		if (err)
			return err;
	}

	stack->blk->ip[stack->pos++] = ip;
	return 0;
}