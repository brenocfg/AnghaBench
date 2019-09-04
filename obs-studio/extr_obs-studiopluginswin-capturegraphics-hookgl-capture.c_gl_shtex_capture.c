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
struct TYPE_2__ {int /*<<< orphan*/  dxgi_swap; int /*<<< orphan*/  gl_dxobj; int /*<<< orphan*/  gl_device; int /*<<< orphan*/  texture; } ;
typedef  int /*<<< orphan*/  GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_DRAW_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_DRAW_FRAMEBUFFER_BINDING ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_BINDING_2D ; 
 int /*<<< orphan*/  IDXGISwapChain_Present (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ data ; 
 int /*<<< orphan*/  glBindFramebuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGetIntegerv (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_copy_backbuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ gl_error (char*,char*) ; 
 int /*<<< orphan*/  jimglDXLockObjectsNV (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jimglDXUnlockObjectsNV (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gl_shtex_capture(void)
{
	GLint last_fbo;
	GLint last_tex;

	jimglDXLockObjectsNV(data.gl_device, 1, &data.gl_dxobj);

	glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &last_fbo);
	if (gl_error("gl_shtex_capture", "failed to get last fbo")) {
		return;
	}

	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_tex);
	if (gl_error("gl_shtex_capture", "failed to get last texture")) {
		return;
	}

	gl_copy_backbuffer(data.texture);

	glBindTexture(GL_TEXTURE_2D, last_tex);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, last_fbo);

	jimglDXUnlockObjectsNV(data.gl_device, 1, &data.gl_dxobj);

	IDXGISwapChain_Present(data.dxgi_swap, 0, 0);
}