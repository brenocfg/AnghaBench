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
struct TYPE_3__ {int wFlags; int /*<<< orphan*/  (* lpFunc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dwUser; int /*<<< orphan*/  wTimerID; scalar_t__ dwTriggerTime; } ;
typedef  TYPE_1__* LPWINE_TIMERENTRY ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  GetCurrentThreadId () ; 
 scalar_t__ GetTickCount () ; 
 int /*<<< orphan*/  PulseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
#define  TIME_CALLBACK_EVENT_PULSE 130 
#define  TIME_CALLBACK_EVENT_SET 129 
#define  TIME_CALLBACK_FUNCTION 128 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ),int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static	void	TIME_TriggerCallBack(LPWINE_TIMERENTRY lpTimer)
{
    TRACE("%04lx:CallBack => lpFunc=%p wTimerID=%04X dwUser=%08lX dwTriggerTime %ld(delta %ld)\n",
	  GetCurrentThreadId(), lpTimer->lpFunc, lpTimer->wTimerID, lpTimer->dwUser,
          lpTimer->dwTriggerTime, GetTickCount() - lpTimer->dwTriggerTime);

    /* - TimeProc callback that is called here is something strange, under Windows 3.1x it is called
     * 		during interrupt time,  is allowed to execute very limited number of API calls (like
     *	    	PostMessage), and must reside in DLL (therefore uses stack of active application). So I
     *       guess current implementation via SetTimer has to be improved upon.
     */
    switch (lpTimer->wFlags & 0x30) {
    case TIME_CALLBACK_FUNCTION:
	    (lpTimer->lpFunc)(lpTimer->wTimerID, 0, lpTimer->dwUser, 0, 0);
	break;
    case TIME_CALLBACK_EVENT_SET:
	SetEvent((HANDLE)lpTimer->lpFunc);
	break;
    case TIME_CALLBACK_EVENT_PULSE:
	PulseEvent((HANDLE)lpTimer->lpFunc);
	break;
    default:
	FIXME("Unknown callback type 0x%04x for mmtime callback (%p), ignored.\n",
	      lpTimer->wFlags, lpTimer->lpFunc);
	break;
    }
}