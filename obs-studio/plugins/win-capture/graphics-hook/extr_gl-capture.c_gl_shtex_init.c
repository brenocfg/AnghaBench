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
struct TYPE_2__ {scalar_t__ handle; int /*<<< orphan*/  format; int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; int /*<<< orphan*/  base_cy; int /*<<< orphan*/  base_cx; int /*<<< orphan*/  shtex_info; } ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  capture_init_shtex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,uintptr_t) ; 
 TYPE_1__ data ; 
 int /*<<< orphan*/  gl_init_fbo () ; 
 int /*<<< orphan*/  gl_shtex_init_d3d11 () ; 
 int /*<<< orphan*/  gl_shtex_init_d3d11_tex () ; 
 int /*<<< orphan*/  gl_shtex_init_gl_tex () ; 
 int /*<<< orphan*/  gl_shtex_init_window () ; 
 int /*<<< orphan*/  hlog (char*) ; 

__attribute__((used)) static bool gl_shtex_init(HWND window)
{
	if (!gl_shtex_init_window()) {
		return false;
	}
	if (!gl_shtex_init_d3d11()) {
		return false;
	}
	if (!gl_shtex_init_d3d11_tex()) {
		return false;
	}
	if (!gl_shtex_init_gl_tex()) {
		return false;
	}
	if (!gl_init_fbo()) {
		return false;
	}
	if (!capture_init_shtex(&data.shtex_info, window, data.base_cx,
				data.base_cy, data.cx, data.cy, data.format,
				true, (uintptr_t)data.handle)) {
		return false;
	}

	hlog("gl shared texture capture successful");
	return true;
}