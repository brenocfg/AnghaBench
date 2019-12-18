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
typedef  scalar_t__ int64 ;
typedef  TYPE_1__* WindowObject ;
struct TYPE_6__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_2__ WindowAggState ;
struct TYPE_5__ {scalar_t__ markpos; scalar_t__ seekpos; int /*<<< orphan*/  readptr; int /*<<< orphan*/  markptr; TYPE_2__* winstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  WindowObjectIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tuplestore_select_read_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplestore_skiptuples (int /*<<< orphan*/ ,scalar_t__,int) ; 

void
WinSetMarkPosition(WindowObject winobj, int64 markpos)
{
	WindowAggState *winstate;

	Assert(WindowObjectIsValid(winobj));
	winstate = winobj->winstate;

	if (markpos < winobj->markpos)
		elog(ERROR, "cannot move WindowObject's mark position backward");
	tuplestore_select_read_pointer(winstate->buffer, winobj->markptr);
	if (markpos > winobj->markpos)
	{
		tuplestore_skiptuples(winstate->buffer,
							  markpos - winobj->markpos,
							  true);
		winobj->markpos = markpos;
	}
	tuplestore_select_read_pointer(winstate->buffer, winobj->readptr);
	if (markpos > winobj->seekpos)
	{
		tuplestore_skiptuples(winstate->buffer,
							  markpos - winobj->seekpos,
							  true);
		winobj->seekpos = markpos;
	}
}