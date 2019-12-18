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
struct TYPE_10__ {TYPE_1__* lpVtbl; } ;
struct TYPE_9__ {int left; int right; int top; int bottom; } ;
struct TYPE_8__ {scalar_t__ (* GetDC ) (TYPE_3__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* ReleaseDC ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__* LPDIRECTDRAWSURFACE ;
typedef  int /*<<< orphan*/  HGDIOBJ ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ HBRUSH ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ CreateSolidBrush (int /*<<< orphan*/ ) ; 
 scalar_t__ DD_OK ; 
 int DD_TEST_HEIGHT ; 
 scalar_t__ DD_TEST_STEP ; 
 int DD_TEST_WIDTH ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__) ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  SM_CXSCREEN ; 
 int /*<<< orphan*/  SM_CYSCREEN ; 
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ ) ; 

VOID DDRedrawFrame(LPDIRECTDRAWSURFACE lpDDSurface)
{
    HDC hdc;

    if (lpDDSurface->lpVtbl->GetDC(lpDDSurface, &hdc) == DD_OK)
    {
        RECT rct;
        HBRUSH BlackBrush, WhiteBrush;
        BOOL Colour = FALSE;

        rct.left = (GetSystemMetrics(SM_CXSCREEN) - DD_TEST_WIDTH)/2;
        rct.right = (GetSystemMetrics(SM_CXSCREEN) - DD_TEST_WIDTH)/2 + DD_TEST_WIDTH;
        rct.top = (GetSystemMetrics(SM_CYSCREEN) - DD_TEST_HEIGHT)/2;
        rct.bottom = (GetSystemMetrics(SM_CYSCREEN) - DD_TEST_HEIGHT)/2 + DD_TEST_HEIGHT;

        BlackBrush = CreateSolidBrush(RGB(0,0,0));
        WhiteBrush = CreateSolidBrush(RGB(255,255,255));

        while((rct.bottom - rct.top) > DD_TEST_STEP){
            (Colour)? FillRect(hdc, &rct, WhiteBrush) : FillRect(hdc, &rct, BlackBrush);
            rct.top += DD_TEST_STEP;
            rct.bottom -= DD_TEST_STEP;
            rct.left += DD_TEST_STEP;
            rct.right -= DD_TEST_STEP;
            Colour = !Colour;
        }
        DeleteObject((HGDIOBJ)BlackBrush);
        DeleteObject((HGDIOBJ)WhiteBrush);
        lpDDSurface->lpVtbl->ReleaseDC(lpDDSurface, hdc);
    }
}