#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wc ;
struct TYPE_4__ {int /*<<< orphan*/  lpszClassName; int /*<<< orphan*/  lpfnWndProc; int /*<<< orphan*/  hInstance; int /*<<< orphan*/  style; } ;
typedef  TYPE_1__ WNDCLASSA ;

/* Variables and functions */
 int /*<<< orphan*/  CS_OWNDC ; 
 int /*<<< orphan*/  DefWindowProc ; 
 int /*<<< orphan*/  GetModuleHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  RegisterClassA (TYPE_1__*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dummy_window_class ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int registered_dummy_window_class ; 

__attribute__((used)) static bool gl_register_dummy_window_class(void)
{
	WNDCLASSA wc;
	if (registered_dummy_window_class)
		return true;

	memset(&wc, 0, sizeof(wc));
	wc.style = CS_OWNDC;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = DefWindowProc;
	wc.lpszClassName = dummy_window_class;

	if (!RegisterClassA(&wc)) {
		blog(LOG_ERROR, "Could not create dummy window class");
		return false;
	}

	registered_dummy_window_class = true;
	return true;
}