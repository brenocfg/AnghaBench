#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_2__ {int right; int left; int bottom; int top; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__* LPRECT ;
typedef  scalar_t__ LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_STYLE ; 
 int GetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_HORZ ; 
 int /*<<< orphan*/  SB_VERT ; 
 int /*<<< orphan*/  SetScrollPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  SetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int WS_HSCROLL ; 
 int WS_VSCROLL ; 
 int /*<<< orphan*/  g_Wnd ; 
 int g_height ; 
 int g_width ; 
 int g_xoff ; 
 scalar_t__ g_xscroll ; 
 int g_yoff ; 
 scalar_t__ g_yscroll ; 

__attribute__((used)) static LRESULT
handle_WM_SIZING(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  LPRECT prect;
  int width;
  int height;
  int style;

  prect = (LPRECT) lParam; /* total window rect */
  width = (prect->right - prect->left) - (g_xoff * 2);
  height = (prect->bottom - prect->top) - (g_yoff + g_xoff);
  if (height < g_height || width < g_width)
  {
    style = GetWindowLongPtr(g_Wnd, GWL_STYLE);
    if (!(style & WS_HSCROLL))
    {
      style |= WS_HSCROLL | WS_VSCROLL;
      SetWindowLongPtr(g_Wnd, GWL_STYLE, style);
      g_xscroll = 0;
      g_yscroll = 0;
      SetScrollPos(g_Wnd, SB_HORZ, g_xscroll, 1);
      SetScrollPos(g_Wnd, SB_VERT, g_yscroll, 1);
    }
  }
  else if (height >= g_height && width >= g_width)
  {
    style = GetWindowLongPtr(g_Wnd, GWL_STYLE);
    if (style & WS_HSCROLL)
    {
      style &= ~WS_HSCROLL;
      style &= ~WS_VSCROLL;
      SetWindowLongPtr(g_Wnd, GWL_STYLE, style);
      g_xscroll = 0;
      g_yscroll = 0;
    }
  }
  return 0;
}