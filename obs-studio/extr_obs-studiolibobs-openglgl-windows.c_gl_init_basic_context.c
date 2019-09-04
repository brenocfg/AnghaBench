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
typedef  int /*<<< orphan*/ * HGLRC ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wglCreateContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wglDeleteContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wgl_make_current (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline HGLRC gl_init_basic_context(HDC hdc)
{
	HGLRC hglrc = wglCreateContext(hdc);
	if (!hglrc) {
		blog(LOG_ERROR, "wglCreateContext failed, %lu", GetLastError());
		return NULL;
	}

	if (!wgl_make_current(hdc, hglrc)) {
		wglDeleteContext(hglrc);
		return NULL;
	}

	return hglrc;
}