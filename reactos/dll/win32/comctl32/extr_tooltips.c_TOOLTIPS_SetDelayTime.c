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
struct TYPE_3__ {int nReshowTime; int nAutoPopTime; int nInitialTime; } ;
typedef  TYPE_1__ TOOLTIPS_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int INT ;
typedef  int DWORD ;

/* Variables and functions */
 int GetDoubleClickTime () ; 
#define  TTDT_AUTOMATIC 131 
#define  TTDT_AUTOPOP 130 
#define  TTDT_INITIAL 129 
#define  TTDT_RESHOW 128 
 int /*<<< orphan*/  WARN (char*,int) ; 

__attribute__((used)) static LRESULT
TOOLTIPS_SetDelayTime (TOOLTIPS_INFO *infoPtr, DWORD duration, INT nTime)
{
    switch (duration) {
    case TTDT_AUTOMATIC:
        if (nTime <= 0)
	    nTime = GetDoubleClickTime();
	infoPtr->nReshowTime    = nTime / 5;
	infoPtr->nAutoPopTime   = nTime * 10;
	infoPtr->nInitialTime   = nTime;
	break;

    case TTDT_RESHOW:
        if(nTime < 0)
	    nTime = GetDoubleClickTime() / 5;
	infoPtr->nReshowTime = nTime;
	break;

    case TTDT_AUTOPOP:
        if(nTime < 0)
	    nTime = GetDoubleClickTime() * 10;
	infoPtr->nAutoPopTime = nTime;
	break;

    case TTDT_INITIAL:
        if(nTime < 0)
	    nTime = GetDoubleClickTime();
	infoPtr->nInitialTime = nTime;
	    break;

    default:
        WARN("Invalid duration flag %x\n", duration);
	break;
    }

    return 0;
}