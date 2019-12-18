#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  wDay; } ;
struct TYPE_7__ {int dwStyle; TYPE_1__ maxSel; TYPE_1__ minSel; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  TYPE_2__ MONTHCAL_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MCS_MULTISELECT ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,...) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT
MONTHCAL_GetSelRange(const MONTHCAL_INFO *infoPtr, SYSTEMTIME *range)
{
  TRACE("%p\n", range);

  if(!range) return FALSE;

  if(infoPtr->dwStyle & MCS_MULTISELECT)
  {
    range[1] = infoPtr->maxSel;
    range[0] = infoPtr->minSel;
    TRACE("[min,max]=[%d %d]\n", infoPtr->minSel.wDay, infoPtr->maxSel.wDay);
    return TRUE;
  }

  return FALSE;
}