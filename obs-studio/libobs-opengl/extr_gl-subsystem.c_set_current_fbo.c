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
struct fbo_info {int /*<<< orphan*/ * cur_zstencil_buffer; int /*<<< orphan*/ * cur_render_target; int /*<<< orphan*/  fbo; } ;
struct TYPE_3__ {struct fbo_info* cur_fbo; } ;
typedef  TYPE_1__ gs_device_t ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_DRAW_FRAMEBUFFER ; 
 int /*<<< orphan*/  gl_bind_framebuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool set_current_fbo(gs_device_t *device, struct fbo_info *fbo)
{
	if (device->cur_fbo != fbo) {
		GLuint fbo_obj = fbo ? fbo->fbo : 0;
		if (!gl_bind_framebuffer(GL_DRAW_FRAMEBUFFER, fbo_obj))
			return false;

		if (device->cur_fbo) {
			device->cur_fbo->cur_render_target = NULL;
			device->cur_fbo->cur_zstencil_buffer = NULL;
		}
	}

	device->cur_fbo = fbo;
	return true;
}