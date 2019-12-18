#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int numalloc; } ;
typedef  int /*<<< orphan*/  SetConstraintTriggerData ;
typedef  TYPE_1__* SetConstraintState ;

/* Variables and functions */
 scalar_t__ MemoryContextAllocZero (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetConstraintStateData ; 
 int /*<<< orphan*/  TopTransactionContext ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trigstates ; 

__attribute__((used)) static SetConstraintState
SetConstraintStateCreate(int numalloc)
{
	SetConstraintState state;

	/* Behave sanely with numalloc == 0 */
	if (numalloc <= 0)
		numalloc = 1;

	/*
	 * We assume that zeroing will correctly initialize the state values.
	 */
	state = (SetConstraintState)
		MemoryContextAllocZero(TopTransactionContext,
							   offsetof(SetConstraintStateData, trigstates) +
							   numalloc * sizeof(SetConstraintTriggerData));

	state->numalloc = numalloc;

	return state;
}