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
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_EXSTYLE ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int GetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int TTS_BALLOON ; 
 int WS_BORDER ; 
 int WS_CHILD ; 
 int WS_CLIPSIBLINGS ; 
 int WS_DLGFRAME ; 
 int WS_EX_TOOLWINDOW ; 
 int WS_POPUP ; 

__attribute__((used)) static LRESULT
TOOLTIPS_NCCreate (HWND hwnd)
{
    DWORD dwStyle = GetWindowLongW (hwnd, GWL_STYLE);
    DWORD dwExStyle = GetWindowLongW (hwnd, GWL_EXSTYLE);

    dwStyle &= ~(WS_CHILD | /*WS_MAXIMIZE |*/ WS_BORDER | WS_DLGFRAME);
    dwStyle |= (WS_POPUP | WS_BORDER | WS_CLIPSIBLINGS);

    /* WS_BORDER only draws a border round the window rect, not the
     * window region, therefore it is useless to us in balloon mode */
    if (dwStyle & TTS_BALLOON) dwStyle &= ~WS_BORDER;

    SetWindowLongW (hwnd, GWL_STYLE, dwStyle);

    dwExStyle |= WS_EX_TOOLWINDOW;
    SetWindowLongW (hwnd, GWL_EXSTYLE, dwExStyle);

    return TRUE;
}