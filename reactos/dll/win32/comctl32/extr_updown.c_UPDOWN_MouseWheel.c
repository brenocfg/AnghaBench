#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int WPARAM ;
typedef  int /*<<< orphan*/  UPDOWN_INFO ;
typedef  int LRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_DECR ; 
 int /*<<< orphan*/  FLAG_INCR ; 
 int GET_WHEEL_DELTA_WPARAM (int) ; 
 int MK_CONTROL ; 
 int MK_SHIFT ; 
 int /*<<< orphan*/  UPDOWN_DoAction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDOWN_GetBuddyInt (int /*<<< orphan*/ *) ; 
 int WHEEL_DELTA ; 
 int /*<<< orphan*/  abs (int) ; 

__attribute__((used)) static LRESULT UPDOWN_MouseWheel(UPDOWN_INFO *infoPtr, WPARAM wParam)
{
    int iWheelDelta = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;

    if (wParam & (MK_SHIFT | MK_CONTROL))
        return 0;

    if (iWheelDelta != 0)
    {
        UPDOWN_GetBuddyInt(infoPtr);
        UPDOWN_DoAction(infoPtr, abs(iWheelDelta), iWheelDelta > 0 ? FLAG_INCR : FLAG_DECR);
    }

    return 1;
}