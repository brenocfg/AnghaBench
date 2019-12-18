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
struct TYPE_4__ {int iHotItem; int /*<<< orphan*/  hwndSelf; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int INT ;
typedef  TYPE_1__ HEADER_INFO ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEADER_RefreshItem (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT
HEADER_MouseLeave (HEADER_INFO *infoPtr)
{
    /* Reset hot-tracked item when mouse leaves control. */
    INT oldHotItem = infoPtr->iHotItem;
    HDC hdc = GetDC (infoPtr->hwndSelf);

    infoPtr->iHotItem = -1;
    if (oldHotItem != -1) HEADER_RefreshItem (infoPtr, oldHotItem);
    ReleaseDC (infoPtr->hwndSelf, hdc);

    return 0;
}