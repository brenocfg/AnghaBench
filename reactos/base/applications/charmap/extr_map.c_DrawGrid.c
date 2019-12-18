#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_11__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_10__ {int /*<<< orphan*/  hdc; int /*<<< orphan*/  rcPaint; } ;
struct TYPE_9__ {TYPE_4__ CellExt; } ;
struct TYPE_8__ {TYPE_2__* pActiveCell; TYPE_2__** Cells; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__* PMAP ;
typedef  TYPE_2__* PCELL ;
typedef  TYPE_3__ PAINTSTRUCT ;
typedef  size_t INT ;

/* Variables and functions */
 int /*<<< orphan*/  DrawActiveCell (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IntersectRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  Rectangle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t XCELLS ; 
 size_t YCELLS ; 

__attribute__((used)) static
VOID
DrawGrid(PMAP infoPtr,
         PAINTSTRUCT *ps)
{
    INT x, y;
    RECT rc;
    PCELL Cell;

    for (y = 0; y < YCELLS; y++)
    for (x = 0; x < XCELLS; x++)
    {
        Cell = &infoPtr->Cells[y][x];

        if (!IntersectRect(&rc,
                           &ps->rcPaint,
                           &Cell->CellExt))
        {
            continue;
        }

        Rectangle(ps->hdc,
                  Cell->CellExt.left,
                  Cell->CellExt.top,
                  Cell->CellExt.right,
                  Cell->CellExt.bottom);

        if (infoPtr->pActiveCell == Cell)
        {
            DrawActiveCell(infoPtr, ps->hdc);
        }
    }
}