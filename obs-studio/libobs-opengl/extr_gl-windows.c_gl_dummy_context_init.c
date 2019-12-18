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
struct dummy_context {int /*<<< orphan*/  hrc; int /*<<< orphan*/  hdc; int /*<<< orphan*/  hwnd; } ;
typedef  int /*<<< orphan*/  PIXELFORMATDESCRIPTOR ;

/* Variables and functions */
 int ChoosePixelFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  SetPixelFormat (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gl_create_dummy_window () ; 
 int /*<<< orphan*/  gl_init_basic_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_register_dummy_window_class () ; 
 int /*<<< orphan*/  init_dummy_pixel_format (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool gl_dummy_context_init(struct dummy_context *dummy)
{
	PIXELFORMATDESCRIPTOR pfd;
	int format_index;

	if (!gl_register_dummy_window_class())
		return false;

	dummy->hwnd = gl_create_dummy_window();
	if (!dummy->hwnd)
		return false;

	dummy->hdc = GetDC(dummy->hwnd);

	init_dummy_pixel_format(&pfd);
	format_index = ChoosePixelFormat(dummy->hdc, &pfd);
	if (!format_index) {
		blog(LOG_ERROR, "Dummy ChoosePixelFormat failed, %lu",
		     GetLastError());
		return false;
	}

	if (!SetPixelFormat(dummy->hdc, format_index, &pfd)) {
		blog(LOG_ERROR, "Dummy SetPixelFormat failed, %lu",
		     GetLastError());
		return false;
	}

	dummy->hrc = gl_init_basic_context(dummy->hdc);
	if (!dummy->hrc) {
		blog(LOG_ERROR, "Failed to initialize dummy context");
		return false;
	}

	return true;
}