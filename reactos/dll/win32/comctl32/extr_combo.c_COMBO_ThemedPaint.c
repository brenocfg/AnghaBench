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
struct TYPE_5__ {int wState; int dwStyle; int /*<<< orphan*/  buttonRect; int /*<<< orphan*/  self; int /*<<< orphan*/  textRect; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HTHEME ;
typedef  TYPE_1__ HEADCOMBO ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int CBF_BUTTONDOWN ; 
 int CBF_HOT ; 
 int /*<<< orphan*/  CBPaintText (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int CBS_DROPDOWNLIST ; 
 scalar_t__ CBS_SIMPLE ; 
 int CBXS_DISABLED ; 
 int CBXS_HOT ; 
 int CBXS_NORMAL ; 
 int CBXS_PRESSED ; 
 scalar_t__ CB_GETTYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  COMBO_XBORDERSIZE () ; 
 int /*<<< orphan*/  COMBO_YBORDERSIZE () ; 
 int /*<<< orphan*/  CP_DROPDOWNBUTTON ; 
 int /*<<< orphan*/  DrawThemeBackground (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EDIT_CONTROL_PADDING () ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InflateRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsRectEmpty (int /*<<< orphan*/ *) ; 
 scalar_t__ IsWindowEnabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT COMBO_ThemedPaint(HTHEME theme, HEADCOMBO *lphc, HDC hdc)
{
    int button_state;
    RECT frame;

    /* paint border */
    if (CB_GETTYPE(lphc) != CBS_SIMPLE)
        GetClientRect(lphc->self, &frame);
    else
    {
        frame = lphc->textRect;
        InflateRect(&frame, EDIT_CONTROL_PADDING(), EDIT_CONTROL_PADDING());
        InflateRect(&frame, COMBO_XBORDERSIZE(), COMBO_YBORDERSIZE());
    }

    DrawThemeBackground(theme, hdc, 0, IsWindowEnabled(lphc->self) ? CBXS_NORMAL : CBXS_DISABLED, &frame, NULL);

    /* Paint button */
    if (!IsRectEmpty(&lphc->buttonRect))
    {
        if (!IsWindowEnabled(lphc->self))
            button_state = CBXS_DISABLED;
        else if (lphc->wState & CBF_BUTTONDOWN)
            button_state = CBXS_PRESSED;
        else if (lphc->wState & CBF_HOT)
            button_state = CBXS_HOT;
        else
            button_state = CBXS_NORMAL;
        DrawThemeBackground(theme, hdc, CP_DROPDOWNBUTTON, button_state, &lphc->buttonRect, NULL);
    }

    if ((lphc->dwStyle & CBS_DROPDOWNLIST) == CBS_DROPDOWNLIST)
        CBPaintText(lphc, hdc);

    return 0;
}