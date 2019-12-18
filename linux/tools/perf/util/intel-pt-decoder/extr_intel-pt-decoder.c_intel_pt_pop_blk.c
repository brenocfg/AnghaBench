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
struct intel_pt_stack {struct intel_pt_blk* spare; struct intel_pt_blk* blk; } ;
struct intel_pt_blk {struct intel_pt_blk* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct intel_pt_blk*) ; 

__attribute__((used)) static void intel_pt_pop_blk(struct intel_pt_stack *stack)
{
	struct intel_pt_blk *blk = stack->blk;

	stack->blk = blk->prev;
	if (!stack->spare)
		stack->spare = blk;
	else
		free(blk);
}