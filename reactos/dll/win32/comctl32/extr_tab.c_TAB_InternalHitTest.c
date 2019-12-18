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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {scalar_t__ uNumItem; } ;
typedef  TYPE_1__ TAB_INFO ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 scalar_t__ PtInRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAB_InternalGetItemRect (TYPE_1__ const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TCHT_NOWHERE ; 
 int /*<<< orphan*/  TCHT_ONITEM ; 

__attribute__((used)) static INT TAB_InternalHitTest (const TAB_INFO *infoPtr, POINT pt, UINT *flags)
{
  RECT rect;
  INT iCount;

  for (iCount = 0; iCount < infoPtr->uNumItem; iCount++)
  {
    TAB_InternalGetItemRect(infoPtr, iCount, &rect, NULL);

    if (PtInRect(&rect, pt))
    {
      *flags = TCHT_ONITEM;
      return iCount;
    }
  }

  *flags = TCHT_NOWHERE;
  return -1;
}