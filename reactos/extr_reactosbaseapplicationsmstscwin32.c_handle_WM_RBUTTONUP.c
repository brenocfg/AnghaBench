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
 scalar_t__ g_mousex ; 
 scalar_t__ g_mousey ; 
 scalar_t__ g_xscroll ; 
 scalar_t__ g_yscroll ; 
 int /*<<< orphan*/  ui_mouse_button (int,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT
handle_WM_RBUTTONUP(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  g_mousex = LOWORD(lParam);
  g_mousey = HIWORD(lParam);
  ui_mouse_button(2, g_mousex + g_xscroll, g_mousey + g_yscroll, 0);
  return 0;
}