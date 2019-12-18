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
struct fbo_info {int dummy; } ;
typedef  int /*<<< orphan*/  gs_zstencil_t ;
typedef  int /*<<< orphan*/  gs_texture_t ;
struct TYPE_4__ {int cur_render_side; int /*<<< orphan*/ * cur_zstencil_buffer; int /*<<< orphan*/ * cur_render_target; } ;
typedef  TYPE_1__ gs_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  attach_rendertarget (struct fbo_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  attach_zstencil (struct fbo_info*,int /*<<< orphan*/ *) ; 
 struct fbo_info* get_fbo_by_tex (int /*<<< orphan*/ *) ; 
 int set_current_fbo (TYPE_1__*,struct fbo_info*) ; 

__attribute__((used)) static bool set_target(gs_device_t *device, gs_texture_t *tex, int side,
		       gs_zstencil_t *zs)
{
	struct fbo_info *fbo;

	if (device->cur_render_target == tex &&
	    device->cur_zstencil_buffer == zs &&
	    device->cur_render_side == side)
		return true;

	device->cur_render_target = tex;
	device->cur_render_side = side;
	device->cur_zstencil_buffer = zs;

	if (!tex)
		return set_current_fbo(device, NULL);

	fbo = get_fbo_by_tex(tex);
	if (!fbo)
		return false;

	set_current_fbo(device, fbo);

	if (!attach_rendertarget(fbo, tex, side))
		return false;
	if (!attach_zstencil(fbo, zs))
		return false;

	return true;
}