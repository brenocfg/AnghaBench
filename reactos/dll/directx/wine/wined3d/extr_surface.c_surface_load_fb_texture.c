#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct wined3d_device* device; } ;
struct wined3d_texture {unsigned int level_count; TYPE_3__ resource; } ;
struct wined3d_surface {struct wined3d_texture* container; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* p_glCopyTexSubImage2D ) (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glReadBuffer ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ gl; } ;
struct wined3d_gl_info {TYPE_2__ gl_ops; } ;
struct wined3d_device {int dummy; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_FRAMEBUFFER ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_surface*) ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 struct wined3d_context* context_acquire (struct wined3d_device*,struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  context_get_offscreen_gl_buffer (struct wined3d_context*) ; 
 struct wined3d_surface* context_get_rt_surface (struct wined3d_context*) ; 
 int /*<<< orphan*/  context_restore (struct wined3d_context*,struct wined3d_surface*) ; 
 int /*<<< orphan*/  device_invalidate_state (struct wined3d_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int surface_get_sub_resource_idx (struct wined3d_surface*) ; 
 scalar_t__ wined3d_resource_is_offscreen (TYPE_3__*) ; 
 int /*<<< orphan*/  wined3d_texture_bind_and_dirtify (struct wined3d_texture*,struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_get_gl_buffer (struct wined3d_texture*) ; 
 int /*<<< orphan*/  wined3d_texture_get_level_height (struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  wined3d_texture_get_level_width (struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  wined3d_texture_get_sub_resource_target (struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  wined3d_texture_prepare_texture (struct wined3d_texture*,struct wined3d_context*,int /*<<< orphan*/ ) ; 

void surface_load_fb_texture(struct wined3d_surface *surface, BOOL srgb, struct wined3d_context *old_ctx)
{
    unsigned int sub_resource_idx = surface_get_sub_resource_idx(surface);
    struct wined3d_texture *texture = surface->container;
    struct wined3d_device *device = texture->resource.device;
    const struct wined3d_gl_info *gl_info;
    struct wined3d_context *context = old_ctx;
    struct wined3d_surface *restore_rt = NULL;
    unsigned int level;
    GLenum target;

    restore_rt = context_get_rt_surface(old_ctx);
    if (restore_rt != surface)
        context = context_acquire(device, texture, sub_resource_idx);
    else
        restore_rt = NULL;

    gl_info = context->gl_info;
    device_invalidate_state(device, STATE_FRAMEBUFFER);

    wined3d_texture_prepare_texture(texture, context, srgb);
    wined3d_texture_bind_and_dirtify(texture, context, srgb);

    TRACE("Reading back offscreen render target %p.\n", surface);

    if (wined3d_resource_is_offscreen(&texture->resource))
        gl_info->gl_ops.gl.p_glReadBuffer(context_get_offscreen_gl_buffer(context));
    else
        gl_info->gl_ops.gl.p_glReadBuffer(wined3d_texture_get_gl_buffer(texture));
    checkGLcall("glReadBuffer");

    level = sub_resource_idx % texture->level_count;
    target = wined3d_texture_get_sub_resource_target(texture, sub_resource_idx);
    gl_info->gl_ops.gl.p_glCopyTexSubImage2D(target, level, 0, 0, 0, 0,
            wined3d_texture_get_level_width(texture, level),
            wined3d_texture_get_level_height(texture, level));
    checkGLcall("glCopyTexSubImage2D");

    if (restore_rt)
        context_restore(context, restore_rt);
}