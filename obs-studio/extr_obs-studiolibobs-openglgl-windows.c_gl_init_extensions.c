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
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_WGL_ARB_create_context ; 
 int /*<<< orphan*/  GLAD_WGL_ARB_create_context_profile ; 
 int /*<<< orphan*/  GLAD_WGL_ARB_pixel_format ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gladLoadWGL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  required_extension_error (char*) ; 

__attribute__((used)) static bool gl_init_extensions(HDC hdc)
{
	if (!gladLoadWGL(hdc)) {
		blog(LOG_ERROR, "Failed to load WGL entry functions.");
		return false;
	}

	if (!GLAD_WGL_ARB_pixel_format) {
		required_extension_error("ARB_pixel_format");
		return false;
	}

	if (!GLAD_WGL_ARB_create_context) {
		required_extension_error("ARB_create_context");
		return false;
	}

	if (!GLAD_WGL_ARB_create_context_profile) {
		required_extension_error("ARB_create_context_profile");
		return false;
	}

	return true;
}