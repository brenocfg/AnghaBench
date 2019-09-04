#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_9__ {int /*<<< orphan*/  hLrgWnd; int /*<<< orphan*/  hParent; int /*<<< orphan*/  hMapWnd; TYPE_1__* pActiveCell; } ;
struct TYPE_8__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
struct TYPE_7__ {int /*<<< orphan*/  CellExt; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__* PMAP ;

/* Variables and functions */
 int /*<<< orphan*/  CopyRect (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InflateRect (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MoveWindow (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ XCELLS ; 
 scalar_t__ XLARGE ; 
 scalar_t__ YCELLS ; 
 scalar_t__ YLARGE ; 

__attribute__((used)) static
VOID
MoveLargeCell(PMAP infoPtr)
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

    MoveWindow(infoPtr->hLrgWnd,
               rLarge.left,
               rLarge.top,
               rLarge.right - rLarge.left,
               rLarge.bottom - rLarge.top,
               TRUE);

    InvalidateRect(infoPtr->hLrgWnd,
                   NULL,
                   TRUE);
}