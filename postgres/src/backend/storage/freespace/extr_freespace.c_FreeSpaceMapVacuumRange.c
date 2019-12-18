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
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  FSM_ROOT_ADDRESS ; 
 int /*<<< orphan*/  fsm_vacuum_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int*) ; 

void
FreeSpaceMapVacuumRange(Relation rel, BlockNumber start, BlockNumber end)
{
	bool		dummy;

	/* Recursively scan the tree, starting at the root */
	if (end > start)
		(void) fsm_vacuum_page(rel, FSM_ROOT_ADDRESS, start, end, &dummy);
}