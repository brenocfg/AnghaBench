#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int style; scalar_t__ self; int /*<<< orphan*/  horz_pos; int /*<<< orphan*/  owner; scalar_t__ font; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_1__ LB_DESCR ;
typedef  int /*<<< orphan*/  INT ;
typedef  scalar_t__ HFONT ;
typedef  scalar_t__ HDC ;
typedef  scalar_t__ HBRUSH ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_GRAYTEXT ; 
 int /*<<< orphan*/  DCX_CACHE ; 
 scalar_t__ GetDCEx (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSysColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsWindowEnabled (scalar_t__) ; 
 int /*<<< orphan*/  IsWindowVisible (scalar_t__) ; 
 int LBS_DISPLAYCHANGED ; 
 int LBS_NOREDRAW ; 
 int LISTBOX_GetItemRect (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LISTBOX_PaintItem (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (scalar_t__,scalar_t__) ; 
 scalar_t__ SelectObject (scalar_t__,scalar_t__) ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowOrgEx (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_CTLCOLORLISTBOX ; 

__attribute__((used)) static void LISTBOX_RepaintItem( LB_DESCR *descr, INT index, UINT action )
{
    HDC hdc;
    RECT rect;
    HFONT oldFont = 0;
    HBRUSH hbrush, oldBrush = 0;

    /* Do not repaint the item if the item is not visible */
    if (!IsWindowVisible(descr->self)) return;
    if (descr->style & LBS_NOREDRAW)
    {
        descr->style |= LBS_DISPLAYCHANGED;
        return;
    }
    if (LISTBOX_GetItemRect( descr, index, &rect ) != 1) return;
    if (!(hdc = GetDCEx( descr->self, 0, DCX_CACHE ))) return;
    if (descr->font) oldFont = SelectObject( hdc, descr->font );
    hbrush = (HBRUSH)SendMessageW( descr->owner, WM_CTLCOLORLISTBOX,
				   (WPARAM)hdc, (LPARAM)descr->self );
    if (hbrush) oldBrush = SelectObject( hdc, hbrush );
    if (!IsWindowEnabled(descr->self))
        SetTextColor( hdc, GetSysColor( COLOR_GRAYTEXT ) );
    SetWindowOrgEx( hdc, descr->horz_pos, 0, NULL );
    LISTBOX_PaintItem( descr, hdc, &rect, index, action, TRUE );
    if (oldFont) SelectObject( hdc, oldFont );
    if (oldBrush) SelectObject( hdc, oldBrush );
    ReleaseDC( descr->self, hdc );
}