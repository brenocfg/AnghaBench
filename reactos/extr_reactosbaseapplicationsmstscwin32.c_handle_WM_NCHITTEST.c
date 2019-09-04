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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ POINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  DefWindowProc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ ScreenToClient (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  g_Wnd ; 
 int /*<<< orphan*/  g_mousex ; 
 int /*<<< orphan*/  g_mousey ; 

__attribute__((used)) static LRESULT
handle_WM_NCHITTEST(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  POINT pt;

  pt.x = LOWORD(lParam);
  pt.y = HIWORD(lParam);
  if (ScreenToClient(g_Wnd, &pt))
  {
    g_mousex = pt.x;
    g_mousey = pt.y;
  }
  return DefWindowProc(hWnd, message, wParam, lParam);
}