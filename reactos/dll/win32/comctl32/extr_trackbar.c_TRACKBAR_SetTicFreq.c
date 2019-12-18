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
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_6__ {int dwStyle; int /*<<< orphan*/  uTicFreq; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int TBS_AUTOTICKS ; 
 int /*<<< orphan*/  TRACKBAR_InvalidateAll (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACKBAR_RecalculateTics (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACKBAR_UpdateThumb (TYPE_1__*) ; 

__attribute__((used)) static inline LRESULT
TRACKBAR_SetTicFreq (TRACKBAR_INFO *infoPtr, WORD wFreq)
{
    if (infoPtr->dwStyle & TBS_AUTOTICKS) {
        infoPtr->uTicFreq = wFreq;
	TRACKBAR_RecalculateTics (infoPtr);
	TRACKBAR_InvalidateAll(infoPtr);
    }

    TRACKBAR_UpdateThumb (infoPtr);
    return 0;
}