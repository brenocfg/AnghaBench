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
struct TYPE_2__ {scalar_t__ left; scalar_t__ top; scalar_t__ right; scalar_t__ bottom; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  DefWindowProc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCursor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_cursor ; 
 scalar_t__ g_mousex ; 
 scalar_t__ g_mousey ; 
 TYPE_1__ g_wnd_clip ; 

__attribute__((used)) static LRESULT
handle_WM_SETCURSOR(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  if (g_mousex >= g_wnd_clip.left &&
      g_mousey >= g_wnd_clip.top &&
      g_mousex < g_wnd_clip.right &&
      g_mousey < g_wnd_clip.bottom)
  {
    SetCursor(g_cursor);
  }
  /* need default behavoir here */
  return DefWindowProc(hWnd, message, wParam, lParam);
}