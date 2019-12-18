#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_10__ {int /*<<< orphan*/  hLrgWnd; int /*<<< orphan*/  hParent; int /*<<< orphan*/  hMapWnd; TYPE_1__* pActiveCell; } ;
struct TYPE_9__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
struct TYPE_8__ {int /*<<< orphan*/  CellExt; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__* PMAP ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CopyRect (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateWindowExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InflateRect (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int WS_CHILDWINDOW ; 
 int WS_VISIBLE ; 
 scalar_t__ XCELLS ; 
 scalar_t__ XLARGE ; 
 scalar_t__ YCELLS ; 
 scalar_t__ YLARGE ; 
 int /*<<< orphan*/  hInstance ; 
 int /*<<< orphan*/  szLrgCellWndClass ; 

__attribute__((used)) static
BOOL
CreateLargeCell(PMAP infoPtr)
{
    RECT rLarge;

    CopyRect(&rLarge,
             &infoPtr->pActiveCell->CellExt);

    MapWindowPoints(infoPtr->hMapWnd,
                    infoPtr->hParent,
                    (VOID*)&rLarge,
                    2);

    InflateRect(&rLarge,
                XLARGE - XCELLS,
                YLARGE - YCELLS);

    infoPtr->hLrgWnd = CreateWindowExW(0,
                                       szLrgCellWndClass,
                                       NULL,
                                       WS_CHILDWINDOW | WS_VISIBLE,
                                       rLarge.left,
                                       rLarge.top,
                                       rLarge.right - rLarge.left,
                                       rLarge.bottom - rLarge.top,
                                       infoPtr->hParent,
                                       NULL,
                                       hInstance,
                                       infoPtr);
    if (!infoPtr->hLrgWnd)
        return FALSE;

    return TRUE;
}