#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int WPARAM ;
struct TYPE_4__ {int nPageY; } ;
typedef  TYPE_1__* LPSCROLLSTATE ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int GetKeyState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELONG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OnScroll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  SB_BOTTOM ; 
 int /*<<< orphan*/  SB_HORZ ; 
 int /*<<< orphan*/  SB_LEFT ; 
 int /*<<< orphan*/  SB_LINEDOWN ; 
 int /*<<< orphan*/  SB_LINELEFT ; 
 int /*<<< orphan*/  SB_LINERIGHT ; 
 int /*<<< orphan*/  SB_LINEUP ; 
 int /*<<< orphan*/  SB_PAGEDOWN ; 
 int /*<<< orphan*/  SB_PAGEUP ; 
 int /*<<< orphan*/  SB_RIGHT ; 
 int /*<<< orphan*/  SB_TOP ; 
 int /*<<< orphan*/  SB_VERT ; 
 int /*<<< orphan*/  VK_CONTROL ; 
#define  VK_DOWN 135 
#define  VK_END 134 
#define  VK_HOME 133 
#define  VK_LEFT 132 
#define  VK_NEXT 131 
#define  VK_PRIOR 130 
#define  VK_RIGHT 129 
#define  VK_UP 128 

void OnKeyScroll(HWND hWnd, WPARAM wParam, LPARAM lParam, LPSCROLLSTATE state)
{
    // NOTE: Windows uses an offset of 16 pixels
    switch (wParam)
    {
        case VK_UP:
            OnScroll(hWnd, SB_VERT, MAKELONG(SB_LINEUP, 0), 5, state);
            break;

        case VK_DOWN:
            OnScroll(hWnd, SB_VERT, MAKELONG(SB_LINEDOWN, 0), 5, state);
            break;

        case VK_LEFT:
            OnScroll(hWnd, SB_HORZ, MAKELONG(SB_LINELEFT, 0), 5, state);
            break;

        case VK_RIGHT:
            OnScroll(hWnd, SB_HORZ, MAKELONG(SB_LINERIGHT, 0), 5, state);
            break;

        case VK_PRIOR:
            OnScroll(hWnd, SB_VERT, MAKELONG(SB_PAGEUP, 0), state->nPageY, state);
            break;

        case VK_NEXT:
            OnScroll(hWnd, SB_VERT, MAKELONG(SB_PAGEDOWN, 0), state->nPageY, state);
            break;

        case VK_HOME:
        {
            OnScroll(hWnd, SB_HORZ, MAKELONG(SB_LEFT, 0), 0, state);
            if (GetKeyState(VK_CONTROL) & 0x8000)
                OnScroll(hWnd, SB_VERT, MAKELONG(SB_TOP, 0), 0, state);
            break;
        }

        case VK_END:
        {
            OnScroll(hWnd, SB_HORZ, MAKELONG(SB_RIGHT, 0), 0, state);
            if (GetKeyState(VK_CONTROL) & 0x8000)
                OnScroll(hWnd, SB_VERT, MAKELONG(SB_BOTTOM, 0), 0, state);
            break;
        }

        default:
            break;
    }
}