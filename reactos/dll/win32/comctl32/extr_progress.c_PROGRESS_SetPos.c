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
typedef  int UINT ;
struct TYPE_6__ {int CurVal; int /*<<< orphan*/  Self; } ;
typedef  TYPE_1__ PROGRESS_INFO ;
typedef  int INT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_STYLE ; 
 int GetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PBS_MARQUEE ; 
 int /*<<< orphan*/  PROGRESS_CoercePos (TYPE_1__*) ; 
 int /*<<< orphan*/  PROGRESS_Invalidate (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  PROGRESS_UpdateMarquee (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACE (char*,int,int) ; 
 int /*<<< orphan*/  UpdateWindow (int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT PROGRESS_SetPos (PROGRESS_INFO *infoPtr, INT pos)
{
    DWORD style = GetWindowLongW(infoPtr->Self, GWL_STYLE);

    if (style & PBS_MARQUEE)
    {
        PROGRESS_UpdateMarquee(infoPtr);
        return 1;
    }
    else
    {
        UINT oldVal;
        oldVal = infoPtr->CurVal;
        if (oldVal != pos) {
	    infoPtr->CurVal = pos;
	    PROGRESS_CoercePos(infoPtr);
	    TRACE("PBM_SETPOS: current pos changed from %d to %d\n", oldVal, infoPtr->CurVal);
            PROGRESS_Invalidate( infoPtr, oldVal, infoPtr->CurVal );
            UpdateWindow( infoPtr->Self );
        }
        return oldVal;
    }
}