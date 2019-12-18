#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int dwStyle; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int TBS_FIXEDLENGTH ; 
 int /*<<< orphan*/  TRACKBAR_AlignBuddies (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACKBAR_CalcChannel (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACKBAR_InitializeThumb (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACKBAR_InvalidateAll (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACKBAR_UpdateThumb (TYPE_1__*) ; 

__attribute__((used)) static LRESULT
TRACKBAR_Size (TRACKBAR_INFO *infoPtr)
{
    if (infoPtr->dwStyle & TBS_FIXEDLENGTH)
    {
        TRACKBAR_CalcChannel(infoPtr);
        TRACKBAR_UpdateThumb(infoPtr);
    }
    else
        TRACKBAR_InitializeThumb(infoPtr);
    TRACKBAR_AlignBuddies (infoPtr);
    TRACKBAR_InvalidateAll(infoPtr);

    return 0;
}