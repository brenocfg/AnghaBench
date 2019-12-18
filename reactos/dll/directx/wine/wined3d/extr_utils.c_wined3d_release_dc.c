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
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  ReleaseDC (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ WindowFromDC (int /*<<< orphan*/ ) ; 

void wined3d_release_dc(HWND window, HDC dc)
{
    /* You'd figure ReleaseDC() would fail if the DC doesn't match the window.
     * However, that's not what actually happens, and there are user32 tests
     * that confirm ReleaseDC() with the wrong window is supposed to succeed.
     * So explicitly check that the DC belongs to the window, since we want to
     * avoid releasing a DC that belongs to some other window if the original
     * window was already destroyed. */
    if (WindowFromDC(dc) != window)
        WARN("DC %p does not belong to window %p.\n", dc, window);
    else if (!ReleaseDC(window, dc))
        ERR("Failed to release device context %p, last error %#x.\n", dc, GetLastError());
}