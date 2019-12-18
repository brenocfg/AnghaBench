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
struct intel_pt_stack {scalar_t__ pos; scalar_t__ blk; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pt_pop_blk (struct intel_pt_stack*) ; 

__attribute__((used)) static void intel_pt_clear_stack(struct intel_pt_stack *stack)
{
	while (stack->blk)
		intel_pt_pop_blk(stack);
	stack->pos = 0;
}