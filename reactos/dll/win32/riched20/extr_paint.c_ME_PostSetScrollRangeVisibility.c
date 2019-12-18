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
struct TYPE_3__ {int fMask; scalar_t__ nMin; scalar_t__ nMax; scalar_t__ nPage; } ;
typedef  TYPE_1__ SCROLLINFO ;
typedef  int BOOL ;

/* Variables and functions */
 int SIF_DISABLENOSCROLL ; 
 int TRUE ; 
 scalar_t__ max (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL ME_PostSetScrollRangeVisibility(SCROLLINFO *si)
{
  if (si->fMask & SIF_DISABLENOSCROLL)
    return TRUE;

  /* This must match the check in SetScrollInfo to determine whether
   * to show or hide the scrollbars. */
  return si->nMin < si->nMax - max(si->nPage - 1, 0);
}