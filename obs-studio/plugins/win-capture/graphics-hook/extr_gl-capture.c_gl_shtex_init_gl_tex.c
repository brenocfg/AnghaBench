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
struct TYPE_2__ {int /*<<< orphan*/  gl_dxobj; int /*<<< orphan*/  texture; int /*<<< orphan*/  d3d11_tex; int /*<<< orphan*/  gl_device; int /*<<< orphan*/  d3d11_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  WGL_ACCESS_WRITE_DISCARD_NV ; 
 TYPE_1__ data ; 
 int /*<<< orphan*/  glGenTextures (int,int /*<<< orphan*/ *) ; 
 scalar_t__ gl_error (char*,char*) ; 
 int /*<<< orphan*/  hlog (char*) ; 
 int /*<<< orphan*/  jimglDXOpenDeviceNV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jimglDXRegisterObjectNV (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool gl_shtex_init_gl_tex(void)
{
	data.gl_device = jimglDXOpenDeviceNV(data.d3d11_device);
	if (!data.gl_device) {
		hlog("gl_shtex_init_gl_tex: failed to open device");
		return false;
	}

	glGenTextures(1, &data.texture);
	if (gl_error("gl_shtex_init_gl_tex", "failed to generate texture")) {
		return false;
	}

	data.gl_dxobj = jimglDXRegisterObjectNV(data.gl_device, data.d3d11_tex,
						data.texture, GL_TEXTURE_2D,
						WGL_ACCESS_WRITE_DISCARD_NV);
	if (!data.gl_dxobj) {
		hlog("gl_shtex_init_gl_tex: failed to register object");
		return false;
	}

	return true;
}