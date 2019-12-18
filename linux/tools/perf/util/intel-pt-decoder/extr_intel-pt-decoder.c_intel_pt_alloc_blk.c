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
struct intel_pt_stack {scalar_t__ pos; struct intel_pt_blk* blk; struct intel_pt_blk* spare; } ;
struct intel_pt_blk {struct intel_pt_blk* prev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct intel_pt_blk* malloc (int) ; 

__attribute__((used)) static int intel_pt_alloc_blk(struct intel_pt_stack *stack)
{
	struct intel_pt_blk *blk;

	if (stack->spare) {
		blk = stack->spare;
		stack->spare = NULL;
	} else {
		blk = malloc(sizeof(struct intel_pt_blk));
		if (!blk)
			return -ENOMEM;
	}

	blk->prev = stack->blk;
	stack->blk = blk;
	stack->pos = 0;
	return 0;
}