#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 scalar_t__ HIWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ LOWORD (int /*<<< orphan*/ ) ; 
 int SB_BOTTOM ; 
 int SB_LINELEFT ; 
 int SB_LINERIGHT ; 
 int SB_PAGELEFT ; 
 int SB_PAGERIGHT ; 
 int SB_THUMBPOSITION ; 
 int SB_TOP ; 
 int /*<<< orphan*/  SB_VERT ; 
 int /*<<< orphan*/  SetScrollPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int UI_MAX (int,int /*<<< orphan*/ ) ; 
 int UI_MIN (int,int) ; 
 int /*<<< orphan*/  g_Wnd ; 
 int g_height ; 
 int g_wnd_cheight ; 
 int g_yscroll ; 
 int /*<<< orphan*/  mi_scroll (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static LRESULT
handle_WM_VSCROLL(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  int code;
  int oldyscroll;

  code = (int) LOWORD(wParam); /* scroll bar value */
  if (code == SB_LINELEFT)
  {
    oldyscroll = g_yscroll;
    g_yscroll--;
    g_yscroll = UI_MAX(g_yscroll, 0);
    SetScrollPos(g_Wnd, SB_VERT, g_yscroll, 1);
    mi_scroll(0, oldyscroll - g_yscroll);
  }
  else if (code == SB_LINERIGHT)
  {
    oldyscroll = g_yscroll;
    g_yscroll++;
    g_yscroll = UI_MIN(g_yscroll, g_height - g_wnd_cheight);
    SetScrollPos(g_Wnd, SB_VERT, g_yscroll, 1);
    mi_scroll(0, oldyscroll - g_yscroll);
  }
  else if (code == SB_PAGELEFT)
  {
    oldyscroll = g_yscroll;
    g_yscroll -= g_wnd_cheight / 2;
    g_yscroll = UI_MAX(g_yscroll, 0);
    SetScrollPos(g_Wnd, SB_VERT, g_yscroll, 1);
    mi_scroll(0, oldyscroll - g_yscroll);
  }
  else if (code == SB_PAGERIGHT)
  {
    oldyscroll = g_yscroll;
    g_yscroll += g_wnd_cheight / 2;
    g_yscroll = UI_MIN(g_yscroll, g_height - g_wnd_cheight);
    SetScrollPos(g_Wnd, SB_VERT, g_yscroll, 1);
    mi_scroll(0, oldyscroll - g_yscroll);
  }
  else if (code == SB_BOTTOM)
  {
    oldyscroll = g_yscroll;
    g_yscroll = g_height - g_wnd_cheight;
    SetScrollPos(g_Wnd, SB_VERT, g_yscroll, 1);
    mi_scroll(0, oldyscroll - g_yscroll);
  }
  else if (code == SB_TOP)
  {
    oldyscroll = g_yscroll;
    g_yscroll = 0;
    SetScrollPos(g_Wnd, SB_VERT, g_yscroll, 1);
    mi_scroll(0, oldyscroll - g_yscroll);
  }
  else if (code == SB_THUMBPOSITION)
  {
    oldyscroll = g_yscroll;
    g_yscroll = (signed short) HIWORD(wParam);
    SetScrollPos(g_Wnd, SB_VERT, g_yscroll, 1);
    mi_scroll(0, oldyscroll - g_yscroll);
  }
  return 0;
}