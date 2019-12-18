#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nTool; int /*<<< orphan*/  nReshowTime; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  bActive; int /*<<< orphan*/  nCurrentTool; } ;
typedef  TYPE_1__ TOOLTIPS_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  FALSE ; 
#define  ID_TIMERLEAVE 130 
#define  ID_TIMERPOP 129 
#define  ID_TIMERSHOW 128 
 int /*<<< orphan*/  KillTimer (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  SetTimer (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* TOOLTIPS_CheckTool (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOOLTIPS_Hide (TYPE_1__*) ; 
 int /*<<< orphan*/  TOOLTIPS_Show (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT
TOOLTIPS_Timer (TOOLTIPS_INFO *infoPtr, INT iTimer)
{
    INT nOldTool;

    TRACE("timer %d (%p) expired\n", iTimer, infoPtr->hwndSelf);

    switch (iTimer) {
    case ID_TIMERSHOW:
        KillTimer (infoPtr->hwndSelf, ID_TIMERSHOW);
	nOldTool = infoPtr->nTool;
	if ((infoPtr->nTool = TOOLTIPS_CheckTool (infoPtr, TRUE)) == nOldTool)
	    TOOLTIPS_Show (infoPtr, FALSE);
	break;

    case ID_TIMERPOP:
        TOOLTIPS_Hide (infoPtr);
	break;

    case ID_TIMERLEAVE:
        nOldTool = infoPtr->nTool;
	infoPtr->nTool = TOOLTIPS_CheckTool (infoPtr, FALSE);
	TRACE("tool (%p) %d %d %d\n", infoPtr->hwndSelf, nOldTool,
	      infoPtr->nTool, infoPtr->nCurrentTool);
	if (infoPtr->nTool != nOldTool) {
	    if(infoPtr->nTool == -1) { /* Moved out of all tools */
	        TOOLTIPS_Hide(infoPtr);
		KillTimer(infoPtr->hwndSelf, ID_TIMERLEAVE);
	    } else if (nOldTool == -1) { /* Moved from outside */
	        ERR("How did this happen?\n");
	    } else { /* Moved from one to another */
	        TOOLTIPS_Hide (infoPtr);
		KillTimer(infoPtr->hwndSelf, ID_TIMERLEAVE);
		if(infoPtr->bActive) {
		    SetTimer (infoPtr->hwndSelf, ID_TIMERSHOW, infoPtr->nReshowTime, 0);
		    TRACE("timer 1 started!\n");
		}
	    }
	}
	break;

    default:
        ERR("Unknown timer id %d\n", iTimer);
	break;
    }
    return 0;
}