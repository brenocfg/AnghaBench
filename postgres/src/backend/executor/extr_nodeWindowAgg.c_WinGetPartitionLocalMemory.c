#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* WindowObject ;
struct TYPE_6__ {void* localmem; TYPE_1__* winstate; } ;
struct TYPE_5__ {int /*<<< orphan*/  partcontext; } ;
typedef  int /*<<< orphan*/  Size ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 void* MemoryContextAllocZero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WindowObjectIsValid (TYPE_2__*) ; 

void *
WinGetPartitionLocalMemory(WindowObject winobj, Size sz)
{
	Assert(WindowObjectIsValid(winobj));
	if (winobj->localmem == NULL)
		winobj->localmem =
			MemoryContextAllocZero(winobj->winstate->partcontext, sz);
	return winobj->localmem;
}