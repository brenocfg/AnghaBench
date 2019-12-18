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
struct TYPE_7__ {int /*<<< orphan*/  right; int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_9__ {int /*<<< orphan*/  hWnd; TYPE_1__ size; int /*<<< orphan*/  control; int /*<<< orphan*/  fWindowless; } ;
struct TYPE_8__ {int /*<<< orphan*/  right; int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
typedef  TYPE_2__ RECTL ;
typedef  int /*<<< orphan*/  IViewObject ;
typedef  TYPE_3__ IOCS ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  DVASPECT_CONTENT ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IViewObject ; 
 int /*<<< orphan*/  IOleObject_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IViewObject_Draw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IViewObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void IOCS_OnDraw( IOCS *This )
{
    IViewObject *view;

    if ( !This->control || !This->fWindowless )
        return;

    if ( SUCCEEDED( IOleObject_QueryInterface( This->control, &IID_IViewObject, (void**)&view ) ) )
    {
        HDC dc = GetDC( This->hWnd );
        RECTL rect;

        rect.left = This->size.left; rect.top = This->size.top;
        rect.bottom = This->size.bottom; rect.right = This->size.right;

        IViewObject_Draw( view, DVASPECT_CONTENT, ~0, NULL, NULL, 0, dc, &rect, &rect, NULL, 0 );
        IViewObject_Release( view );
        ReleaseDC( This->hWnd, dc );
    }
}