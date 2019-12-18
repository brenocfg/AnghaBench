#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int message; int /*<<< orphan*/  hwnd; int /*<<< orphan*/  lParam; } ;
struct TYPE_11__ {short x; short y; } ;
struct TYPE_10__ {int nTool; int nCurrentTool; int /*<<< orphan*/  nInitialTime; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  bActive; int /*<<< orphan*/  nAutoPopTime; int /*<<< orphan*/  nReshowTime; } ;
typedef  TYPE_1__ TOOLTIPS_INFO ;
typedef  TYPE_2__ POINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_3__* LPMSG ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID_TIMERLEAVE ; 
 int /*<<< orphan*/  ID_TIMERPOP ; 
 int /*<<< orphan*/  ID_TIMERSHOW ; 
 int /*<<< orphan*/  KillTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TOOLTIPS_GetToolFromPoint (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  TOOLTIPS_Hide (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
#define  WM_LBUTTONDOWN 134 
#define  WM_LBUTTONUP 133 
#define  WM_MBUTTONDOWN 132 
#define  WM_MBUTTONUP 131 
#define  WM_MOUSEMOVE 130 
#define  WM_RBUTTONDOWN 129 
#define  WM_RBUTTONUP 128 
 int /*<<< orphan*/  wine_dbgstr_point (TYPE_2__*) ; 

__attribute__((used)) static LRESULT
TOOLTIPS_RelayEvent (TOOLTIPS_INFO *infoPtr, LPMSG lpMsg)
{
    POINT pt;
    INT nOldTool;

    if (!lpMsg) {
	ERR("lpMsg == NULL\n");
	return 0;
    }

    switch (lpMsg->message) {
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	    TOOLTIPS_Hide (infoPtr);
	    break;

	case WM_MOUSEMOVE:
	    pt.x = (short)LOWORD(lpMsg->lParam);
	    pt.y = (short)HIWORD(lpMsg->lParam);
	    nOldTool = infoPtr->nTool;
	    infoPtr->nTool = TOOLTIPS_GetToolFromPoint(infoPtr, lpMsg->hwnd,
						       &pt);
	    TRACE("tool (%p) %d %d %d\n", infoPtr->hwndSelf, nOldTool,
		  infoPtr->nTool, infoPtr->nCurrentTool);
            TRACE("WM_MOUSEMOVE (%p %s)\n", infoPtr->hwndSelf, wine_dbgstr_point(&pt));

	    if (infoPtr->nTool != nOldTool) {
	        if(infoPtr->nTool == -1) { /* Moved out of all tools */
		    TOOLTIPS_Hide(infoPtr);
		    KillTimer(infoPtr->hwndSelf, ID_TIMERLEAVE);
		} else if (nOldTool == -1) { /* Moved from outside */
		    if(infoPtr->bActive) {
		        SetTimer(infoPtr->hwndSelf, ID_TIMERSHOW, infoPtr->nInitialTime, 0);
                        TRACE("timer 1 started\n");
		    }
		} else { /* Moved from one to another */
		    TOOLTIPS_Hide (infoPtr);
		    KillTimer(infoPtr->hwndSelf, ID_TIMERLEAVE);
		    if(infoPtr->bActive) {
		        SetTimer (infoPtr->hwndSelf, ID_TIMERSHOW, infoPtr->nReshowTime, 0);
                        TRACE("timer 1 started\n");
		    }
		}
	    } else if(infoPtr->nCurrentTool != -1) { /* restart autopop */
	        KillTimer(infoPtr->hwndSelf, ID_TIMERPOP);
		SetTimer(infoPtr->hwndSelf, ID_TIMERPOP, infoPtr->nAutoPopTime, 0);
		TRACE("timer 2 restarted\n");
	    } else if(infoPtr->nTool != -1 && infoPtr->bActive) {
                /* previous show attempt didn't result in tooltip so try again */
		SetTimer(infoPtr->hwndSelf, ID_TIMERSHOW, infoPtr->nInitialTime, 0);
                TRACE("timer 1 started\n");
	    }
	    break;
    }

    return 0;
}