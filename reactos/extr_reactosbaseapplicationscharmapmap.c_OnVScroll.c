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
struct TYPE_8__ {int cy; } ;
struct TYPE_10__ {int iYStart; int /*<<< orphan*/ * hLrgWnd; int /*<<< orphan*/  hMapWnd; TYPE_1__ CellSize; int /*<<< orphan*/  NumRows; } ;
struct TYPE_9__ {int top; int bottom; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__* PMAP ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  SB_LINEDOWN 132 
#define  SB_LINEUP 131 
#define  SB_PAGEDOWN 130 
#define  SB_PAGEUP 129 
#define  SB_THUMBTRACK 128 
 int /*<<< orphan*/  SB_VERT ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SW_INVALIDATE ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  ScrollWindowEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetScrollPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ YCELLS ; 
 scalar_t__ abs (int) ; 
 int max (int /*<<< orphan*/ ,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
VOID
OnVScroll(PMAP infoPtr,
          INT Value,
          INT Pos)
{
    INT iYDiff, iOldYStart = infoPtr->iYStart;

    switch (Value)
    {
        case SB_LINEUP:
            infoPtr->iYStart -=  1;
            break;

        case SB_LINEDOWN:
            infoPtr->iYStart +=  1;
            break;

        case SB_PAGEUP:
            infoPtr->iYStart -= YCELLS;
            break;

        case SB_PAGEDOWN:
            infoPtr->iYStart += YCELLS;
            break;

        case SB_THUMBTRACK:
            infoPtr->iYStart = Pos;
            break;

       default:
            break;
       }

    infoPtr->iYStart = max(0, infoPtr->iYStart);
    infoPtr->iYStart = min(infoPtr->iYStart, infoPtr->NumRows);

    iYDiff = iOldYStart - infoPtr->iYStart;
    if (iYDiff)
    {
        if (infoPtr->hLrgWnd != NULL)
        {
            ShowWindow(infoPtr->hLrgWnd, SW_HIDE);
        }

        SetScrollPos(infoPtr->hMapWnd,
                     SB_VERT,
                     infoPtr->iYStart,
                     TRUE);

        if (abs(iYDiff) < YCELLS)
        {
            RECT rect;
            GetClientRect(infoPtr->hMapWnd, &rect);
            rect.top += 2;
            rect.bottom -= 2;
            ScrollWindowEx(infoPtr->hMapWnd,
                           0,
                           iYDiff * infoPtr->CellSize.cy,
                           &rect,
                           &rect,
                           NULL,
                           NULL,
                           SW_INVALIDATE);
        }
        else
        {
            InvalidateRect(infoPtr->hMapWnd,
                           NULL,
                           TRUE);
        }

        if (infoPtr->hLrgWnd != NULL)
        {
            ShowWindow(infoPtr->hLrgWnd, SW_SHOW);
        }
    }
}