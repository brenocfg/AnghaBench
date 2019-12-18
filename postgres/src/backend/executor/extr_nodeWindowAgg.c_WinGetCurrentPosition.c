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
typedef  TYPE_2__* WindowObject ;
struct TYPE_6__ {TYPE_1__* winstate; } ;
struct TYPE_5__ {int /*<<< orphan*/  currentpos; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WindowObjectIsValid (TYPE_2__*) ; 

int64
WinGetCurrentPosition(WindowObject winobj)
{
	Assert(WindowObjectIsValid(winobj));
	return winobj->winstate->currentpos;
}