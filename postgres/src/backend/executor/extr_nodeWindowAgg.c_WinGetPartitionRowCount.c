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
typedef  int /*<<< orphan*/  int64 ;
typedef  TYPE_1__* WindowObject ;
struct TYPE_6__ {int /*<<< orphan*/  spooled_rows; } ;
struct TYPE_5__ {TYPE_2__* winstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WindowObjectIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  spool_tuples (TYPE_2__*,int) ; 

int64
WinGetPartitionRowCount(WindowObject winobj)
{
	Assert(WindowObjectIsValid(winobj));
	spool_tuples(winobj->winstate, -1);
	return winobj->winstate->spooled_rows;
}