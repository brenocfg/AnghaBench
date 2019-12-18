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
struct TYPE_2__ {int /*<<< orphan*/  hdc; int /*<<< orphan*/  hwnd; } ;
struct gl_platform {TYPE_1__ window; } ;

/* Variables and functions */
 int /*<<< orphan*/  CreateWindowExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DUMMY_WNDCLASS ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetModuleHandleW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  WS_POPUP ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool create_dummy_window(struct gl_platform *plat)
{
	plat->window.hwnd = CreateWindowExA(0, DUMMY_WNDCLASS,
					    "OpenGL Dummy Window", WS_POPUP, 0,
					    0, 1, 1, NULL, NULL,
					    GetModuleHandleW(NULL), NULL);
	if (!plat->window.hwnd) {
		blog(LOG_ERROR, "Failed to create dummy GL window, %lu",
		     GetLastError());
		return false;
	}

	plat->window.hdc = GetDC(plat->window.hwnd);
	if (!plat->window.hdc) {
		blog(LOG_ERROR, "Failed to get dummy GL window DC (%lu)",
		     GetLastError());
		return false;
	}

	return true;
}