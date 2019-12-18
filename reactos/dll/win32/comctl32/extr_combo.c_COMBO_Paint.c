#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int wState; int /*<<< orphan*/  textRect; int /*<<< orphan*/  buttonRect; int /*<<< orphan*/  self; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__ HEADCOMBO ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ HBRUSH ;

/* Variables and functions */
 int CBF_EDIT ; 
 int /*<<< orphan*/  CBPaintBorder (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CBPaintButton (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CBPaintText (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ CBS_DROPDOWNLIST ; 
 scalar_t__ CB_GETTYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  COLOR_WINDOW ; 
 scalar_t__ COMBO_PrepareColors (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_CONTROL_PADDING () ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  FrameRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSysColorBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InflateRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsRectEmpty (int /*<<< orphan*/ *) ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT COMBO_Paint(HEADCOMBO *lphc, HDC hdc)
{
    HBRUSH hPrevBrush, hBkgBrush;

    TRACE("hdc=%p\n", hdc);

    /*
     * Retrieve the background brush and select it in the
     * DC.
     */
    hBkgBrush = COMBO_PrepareColors(lphc, hdc);
    hPrevBrush = SelectObject(hdc, hBkgBrush);
    if (!(lphc->wState & CBF_EDIT))
        FillRect(hdc, &lphc->textRect, hBkgBrush);

    /*
     * In non 3.1 look, there is a sunken border on the combobox
     */
    CBPaintBorder(lphc->self, lphc, hdc);

    if (!IsRectEmpty(&lphc->buttonRect))
        CBPaintButton(lphc, hdc, lphc->buttonRect);

    /* paint the edit control padding area */
    if (CB_GETTYPE(lphc) != CBS_DROPDOWNLIST)
    {
        RECT rPadEdit = lphc->textRect;

        InflateRect(&rPadEdit, EDIT_CONTROL_PADDING(), EDIT_CONTROL_PADDING());

        FrameRect(hdc, &rPadEdit, GetSysColorBrush(COLOR_WINDOW));
    }

    if (!(lphc->wState & CBF_EDIT))
        CBPaintText( lphc, hdc );

    if (hPrevBrush)
        SelectObject( hdc, hPrevBrush );

    return 0;
}