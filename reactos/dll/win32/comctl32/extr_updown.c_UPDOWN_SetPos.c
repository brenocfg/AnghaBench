#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int CurVal; int MinVal; int MaxVal; } ;
typedef  TYPE_1__ UPDOWN_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  UPDOWN_InBounds (TYPE_1__*,int) ; 
 int /*<<< orphan*/  UPDOWN_SetBuddyInt (TYPE_1__*) ; 

__attribute__((used)) static int UPDOWN_SetPos(UPDOWN_INFO *infoPtr, int pos)
{
    int ret = infoPtr->CurVal;

    if(!UPDOWN_InBounds(infoPtr, pos)) {
        if((infoPtr->MinVal < infoPtr->MaxVal && pos < infoPtr->MinVal)
                || (infoPtr->MinVal > infoPtr->MaxVal && pos > infoPtr->MinVal))
            pos = infoPtr->MinVal;
        else
            pos = infoPtr->MaxVal;
    }

    infoPtr->CurVal = pos;
    UPDOWN_SetBuddyInt(infoPtr);

    if(!UPDOWN_InBounds(infoPtr, ret)) {
        if((infoPtr->MinVal < infoPtr->MaxVal && ret < infoPtr->MinVal)
                || (infoPtr->MinVal > infoPtr->MaxVal && ret > infoPtr->MinVal))
            ret = infoPtr->MinVal;
        else
            ret = infoPtr->MaxVal;
    }
    return ret;
}