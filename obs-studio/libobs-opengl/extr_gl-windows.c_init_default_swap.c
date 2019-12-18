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
struct TYPE_2__ {int /*<<< orphan*/  hdc; } ;
struct gl_platform {TYPE_1__ window; } ;
typedef  int /*<<< orphan*/  gs_device_t ;
typedef  int /*<<< orphan*/  PIXELFORMATDESCRIPTOR ;

/* Variables and functions */
 int /*<<< orphan*/  gl_setpixelformat (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool init_default_swap(struct gl_platform *plat, gs_device_t *device,
			      int pixel_format, PIXELFORMATDESCRIPTOR *pfd)
{
	if (!gl_setpixelformat(plat->window.hdc, pixel_format, pfd))
		return false;

	return true;
}