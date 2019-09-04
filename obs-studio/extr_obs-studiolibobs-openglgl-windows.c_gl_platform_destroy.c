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
struct TYPE_2__ {scalar_t__ hwnd; scalar_t__ hdc; } ;
struct gl_platform {TYPE_1__ window; scalar_t__ hrc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseDC (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bfree (struct gl_platform*) ; 
 int /*<<< orphan*/  wglDeleteContext (scalar_t__) ; 
 int /*<<< orphan*/  wglMakeCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void gl_platform_destroy(struct gl_platform *plat)
{
	if (plat) {
		if (plat->hrc) {
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(plat->hrc);
		}

		if (plat->window.hdc)
			ReleaseDC(plat->window.hwnd, plat->window.hdc);
		if (plat->window.hwnd)
			DestroyWindow(plat->window.hwnd);

		bfree(plat);
	}
}