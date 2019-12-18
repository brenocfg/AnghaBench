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
typedef  scalar_t__ WNDPROC ;
struct TYPE_3__ {int /*<<< orphan*/  lpszClassName; scalar_t__ lpfnWndProc; int /*<<< orphan*/  hInstance; int /*<<< orphan*/  style; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ WNDCLASSA ;

/* Variables and functions */
 int /*<<< orphan*/  CS_OWNDC ; 
 int /*<<< orphan*/  DUMMY_WNDCLASS ; 
 scalar_t__ DefWindowProcA ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetModuleHandleW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  RegisterClassA (TYPE_1__*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool register_dummy_class(void)
{
	static bool created = false;

	WNDCLASSA wc = {0};
	wc.style = CS_OWNDC;
	wc.hInstance = GetModuleHandleW(NULL);
	wc.lpfnWndProc = (WNDPROC)DefWindowProcA;
	wc.lpszClassName = DUMMY_WNDCLASS;

	if (created)
		return true;

	if (!RegisterClassA(&wc)) {
		blog(LOG_ERROR, "Failed to register dummy GL window class, %lu",
		     GetLastError());
		return false;
	}

	created = true;
	return true;
}