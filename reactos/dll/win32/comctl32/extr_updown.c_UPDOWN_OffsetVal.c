#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ CurVal; int dwStyle; scalar_t__ MaxVal; scalar_t__ MinVal; } ;
typedef  TYPE_1__ UPDOWN_INFO ;
typedef  int BOOL ;

/* Variables and functions */
 int UDS_WRAP ; 
 int /*<<< orphan*/  UPDOWN_InBounds (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static BOOL UPDOWN_OffsetVal(UPDOWN_INFO *infoPtr, int delta)
{
    /* check if we can do the modification first */
    if(!UPDOWN_InBounds (infoPtr, infoPtr->CurVal+delta)) {
        if (infoPtr->dwStyle & UDS_WRAP) {
            delta += (delta < 0 ? -1 : 1) *
		     (infoPtr->MaxVal < infoPtr->MinVal ? -1 : 1) *
		     (infoPtr->MinVal - infoPtr->MaxVal) +
		     (delta < 0 ? 1 : -1);
        } else if ((infoPtr->MaxVal > infoPtr->MinVal && infoPtr->CurVal+delta > infoPtr->MaxVal)
                || (infoPtr->MaxVal < infoPtr->MinVal && infoPtr->CurVal+delta < infoPtr->MaxVal)) {
            delta = infoPtr->MaxVal - infoPtr->CurVal;
        } else {
            delta = infoPtr->MinVal - infoPtr->CurVal;
        }
    }

    infoPtr->CurVal += delta;
    return delta != 0;
}