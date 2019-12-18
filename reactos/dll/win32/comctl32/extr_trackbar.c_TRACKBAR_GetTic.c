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
struct TYPE_3__ {size_t uNumTics; int* tics; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  int LONG ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  comp_tics ; 
 int /*<<< orphan*/  qsort (int*,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline LONG
TRACKBAR_GetTic (const TRACKBAR_INFO *infoPtr, INT iTic)
{
    if ((iTic < 0) || (iTic >= infoPtr->uNumTics) || !infoPtr->tics)
	return -1;

    qsort(infoPtr->tics, infoPtr->uNumTics, sizeof(DWORD), comp_tics);
    return infoPtr->tics[iTic];
}