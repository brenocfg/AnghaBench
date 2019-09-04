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
struct intel_pt_stack {int /*<<< orphan*/  spare; int /*<<< orphan*/  blk; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pt_clear_stack (struct intel_pt_stack*) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_pt_free_stack(struct intel_pt_stack *stack)
{
	intel_pt_clear_stack(stack);
	zfree(&stack->blk);
	zfree(&stack->spare);
}