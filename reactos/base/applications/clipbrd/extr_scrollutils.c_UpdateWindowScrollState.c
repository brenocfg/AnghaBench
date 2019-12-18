#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  si ;
struct TYPE_11__ {void* nPageX; void* nPageY; void* CurrentY; void* MaxY; void* nMaxHeight; void* CurrentX; void* MaxX; void* nMaxWidth; } ;
struct TYPE_10__ {void* right; void* bottom; } ;
struct TYPE_9__ {int cbSize; int fMask; void* nPage; void* nPos; void* nMax; scalar_t__ nMin; } ;
typedef  TYPE_1__ SCROLLINFO ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__* LPSCROLLSTATE ;
typedef  void* INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  SB_HORZ ; 
 int /*<<< orphan*/  SB_VERT ; 
 int SIF_DISABLENOSCROLL ; 
 int SIF_PAGE ; 
 int SIF_POS ; 
 int SIF_RANGE ; 
 int /*<<< orphan*/  SetRectEmpty (TYPE_2__*) ; 
 int /*<<< orphan*/  SetScrollInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 void* max (void*,int /*<<< orphan*/ ) ; 
 void* min (void*,void*) ; 

void UpdateWindowScrollState(HWND hWnd, INT nMaxWidth, INT nMaxHeight, LPSCROLLSTATE lpState)
{
    RECT rc;
    SCROLLINFO si;

    if (!GetClientRect(hWnd, &rc))
        SetRectEmpty(&rc);

    ZeroMemory(&si, sizeof(si));
    si.cbSize = sizeof(si);
    si.fMask  = SIF_RANGE | SIF_PAGE | SIF_POS | SIF_DISABLENOSCROLL;

    lpState->nMaxWidth = nMaxWidth;
    lpState->MaxX = max(nMaxWidth - rc.right, 0);
    lpState->CurrentX = min(lpState->CurrentX, lpState->MaxX);
    lpState->nPageX = rc.right;
    si.nMin  = 0;
    si.nMax  = nMaxWidth;
    si.nPage = lpState->nPageX;
    si.nPos  = lpState->CurrentX;
    SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);

    lpState->nMaxHeight = nMaxHeight;
    lpState->MaxY = max(nMaxHeight - rc.bottom, 0);
    lpState->CurrentY = min(lpState->CurrentY, lpState->MaxY);
    lpState->nPageY = rc.bottom;
    si.nMin  = 0;
    si.nMax  = nMaxHeight;
    si.nPage = lpState->nPageY;
    si.nPos  = lpState->CurrentY;
    SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
}