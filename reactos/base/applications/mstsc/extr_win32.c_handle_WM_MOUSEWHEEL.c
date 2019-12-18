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
 int /*<<< orphan*/  ui_mouse_button (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static LRESULT
handle_WM_MOUSEWHEEL(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  int delta;

  delta = ((signed short)HIWORD(wParam)); /* GET_WHEEL_DELTA_WPARAM(wParam); */
  if (delta > 0)
  {
    ui_mouse_button(4, 0, 0, 1);
    ui_mouse_button(4, 0, 0, 0);
  }
  else
  {
    ui_mouse_button(5, 0, 0, 1);
    ui_mouse_button(5, 0, 0, 0);
  }
  return 0;
}