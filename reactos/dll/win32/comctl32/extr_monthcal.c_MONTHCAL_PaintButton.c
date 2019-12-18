#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum nav_direction { ____Placeholder_nav_direction } nav_direction ;
struct TYPE_3__ {int status; int dwStyle; int /*<<< orphan*/  titlebtnprev; int /*<<< orphan*/  titlebtnnext; int /*<<< orphan*/  hwndSelf; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__ MONTHCAL_INFO ;
typedef  scalar_t__ HTHEME ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int BOOL ;

/* Variables and functions */
#define  ABS_LEFTDISABLED 133 
#define  ABS_LEFTNORMAL 132 
#define  ABS_LEFTPRESSED 131 
#define  ABS_RIGHTDISABLED 130 
#define  ABS_RIGHTNORMAL 129 
#define  ABS_RIGHTPRESSED 128 
 int DFCS_INACTIVE ; 
 int DFCS_PUSHED ; 
 int DFCS_SCROLLLEFT ; 
 int DFCS_SCROLLRIGHT ; 
 int /*<<< orphan*/  DFC_SCROLL ; 
 int DIRECTION_FORWARD ; 
 int /*<<< orphan*/  DrawFrameControl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DrawThemeBackground (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ GetWindowTheme (int /*<<< orphan*/ ) ; 
 int MC_NEXTPRESSED ; 
 int MC_PREVPRESSED ; 
 int /*<<< orphan*/  SBP_ARROWBTN ; 
 int WS_DISABLED ; 

__attribute__((used)) static void MONTHCAL_PaintButton(MONTHCAL_INFO *infoPtr, HDC hdc, enum nav_direction button)
{
    HTHEME theme = GetWindowTheme (infoPtr->hwndSelf);
    RECT *r = button == DIRECTION_FORWARD ? &infoPtr->titlebtnnext : &infoPtr->titlebtnprev;
    BOOL pressed = button == DIRECTION_FORWARD ? infoPtr->status & MC_NEXTPRESSED :
                                                 infoPtr->status & MC_PREVPRESSED;
    if (theme)
    {
        static const int states[] = {
            /* Prev button */
            ABS_LEFTNORMAL,  ABS_LEFTPRESSED,  ABS_LEFTDISABLED,
            /* Next button */
            ABS_RIGHTNORMAL, ABS_RIGHTPRESSED, ABS_RIGHTDISABLED
        };
        int stateNum = button == DIRECTION_FORWARD ? 3 : 0;
        if (pressed)
            stateNum += 1;
        else
        {
            if (infoPtr->dwStyle & WS_DISABLED) stateNum += 2;
        }
        DrawThemeBackground (theme, hdc, SBP_ARROWBTN, states[stateNum], r, NULL);
    }
    else
    {
        int style = button == DIRECTION_FORWARD ? DFCS_SCROLLRIGHT : DFCS_SCROLLLEFT;
        if (pressed)
            style |= DFCS_PUSHED;
        else
        {
            if (infoPtr->dwStyle & WS_DISABLED) style |= DFCS_INACTIVE;
        }
        
        DrawFrameControl(hdc, r, DFC_SCROLL, style);
    }
}