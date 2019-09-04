#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_24__ {int dwSize; scalar_t__ dwFillColor; } ;
struct TYPE_23__ {TYPE_1__* lpVtbl; } ;
struct TYPE_22__ {scalar_t__ bottom; scalar_t__ top; scalar_t__ right; scalar_t__ left; } ;
struct TYPE_21__ {scalar_t__ (* GetDC ) (TYPE_3__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* Blt ) (TYPE_3__*,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int,TYPE_4__*) ;int /*<<< orphan*/  (* Flip ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ReleaseDC ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__* LPDIRECTDRAWSURFACE ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  int /*<<< orphan*/  DDBlitFx ;
typedef  TYPE_4__ DDBLTFX ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int DDBLT_COLORFILL ; 
 int DDBLT_WAIT ; 
 int /*<<< orphan*/  DDFLIP_WAIT ; 
 scalar_t__ DD_OK ; 
 scalar_t__ DD_SQUARE_SIZE ; 
 scalar_t__ DD_TEST_HEIGHT ; 
 scalar_t__ DD_TEST_WIDTH ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_4__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int,TYPE_4__*) ; 
 scalar_t__ stub2 (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__*,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int,TYPE_4__*) ; 

VOID DDUpdateFrame(LPDIRECTDRAWSURFACE lpDDPrimarySurface ,LPDIRECTDRAWSURFACE lpDDBackBuffer, BOOL Fullscreen, INT *posX, INT *posY, INT *gainX, INT *gainY, RECT *rectDD)
{
    HDC hdc;
    DDBLTFX DDBlitFx;

    /* clear back buffer and paint it black */
    ZeroMemory(&DDBlitFx, sizeof(DDBlitFx));
    DDBlitFx.dwSize = sizeof(DDBlitFx);
    DDBlitFx.dwFillColor = 0;

    lpDDBackBuffer->lpVtbl->Blt(lpDDBackBuffer, NULL, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &DDBlitFx);

    if (lpDDBackBuffer->lpVtbl->GetDC(lpDDBackBuffer, &hdc) == DD_OK)
    {
        RECT rct;
        HBRUSH WhiteBrush;

        rct.left = *posX;
        rct.right = *posX+DD_SQUARE_SIZE;
        rct.top = *posY;
        rct.bottom = *posY+DD_SQUARE_SIZE;

        WhiteBrush = CreateSolidBrush(RGB(255,255,255));
        FillRect(hdc, &rct, WhiteBrush);

        if(*posX >= (DD_TEST_WIDTH - DD_SQUARE_SIZE)) *gainX = -(*gainX);
        if(*posY >= (DD_TEST_HEIGHT - DD_SQUARE_SIZE)) *gainY = -(*gainY);
        if(*posX < 0) *gainX = -1*(*gainX);
        if(*posY < 0) *gainY = -1*(*gainY);

        *posX += *gainX;
        *posY += *gainY;

        lpDDBackBuffer->lpVtbl->ReleaseDC(lpDDBackBuffer, hdc);

        if(Fullscreen)
        {
            lpDDPrimarySurface->lpVtbl->Flip(lpDDPrimarySurface, NULL, DDFLIP_WAIT);
        }
        else
        {
            lpDDPrimarySurface->lpVtbl->Blt(lpDDPrimarySurface, rectDD, lpDDBackBuffer, NULL, DDBLT_WAIT, NULL);
        }
    }
}