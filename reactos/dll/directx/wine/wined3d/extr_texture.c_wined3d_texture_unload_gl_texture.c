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
struct TYPE_5__ {struct wined3d_device* device; } ;
struct TYPE_6__ {scalar_t__ name; } ;
struct wined3d_texture {TYPE_2__ resource; scalar_t__ rb_resolved; scalar_t__ rb_multisample; TYPE_3__ texture_srgb; TYPE_3__ texture_rgb; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* glDeleteRenderbuffers ) (int,scalar_t__*) ;} ;
struct wined3d_gl_info {TYPE_1__ fbo_ops; } ;
struct wined3d_device {int dummy; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 struct wined3d_context* context_acquire (struct wined3d_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_gl_resource_released (struct wined3d_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_release (struct wined3d_context*) ; 
 int /*<<< orphan*/  gltexture_delete (struct wined3d_device*,struct wined3d_gl_info*,TYPE_3__*) ; 
 int /*<<< orphan*/  resource_unload (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (int,scalar_t__*) ; 
 int /*<<< orphan*/  wined3d_texture_set_dirty (struct wined3d_texture*) ; 

__attribute__((used)) static void wined3d_texture_unload_gl_texture(struct wined3d_texture *texture)
{
    struct wined3d_device *device = texture->resource.device;
    const struct wined3d_gl_info *gl_info = NULL;
    struct wined3d_context *context = NULL;

    if (texture->texture_rgb.name || texture->texture_srgb.name
            || texture->rb_multisample || texture->rb_resolved)
    {
        context = context_acquire(device, NULL, 0);
        gl_info = context->gl_info;
    }

    if (texture->texture_rgb.name)
        gltexture_delete(device, context->gl_info, &texture->texture_rgb);

    if (texture->texture_srgb.name)
        gltexture_delete(device, context->gl_info, &texture->texture_srgb);

    if (texture->rb_multisample)
    {
        TRACE("Deleting multisample renderbuffer %u.\n", texture->rb_multisample);
        context_gl_resource_released(device, texture->rb_multisample, TRUE);
        gl_info->fbo_ops.glDeleteRenderbuffers(1, &texture->rb_multisample);
        texture->rb_multisample = 0;
    }

    if (texture->rb_resolved)
    {
        TRACE("Deleting resolved renderbuffer %u.\n", texture->rb_resolved);
        context_gl_resource_released(device, texture->rb_resolved, TRUE);
        gl_info->fbo_ops.glDeleteRenderbuffers(1, &texture->rb_resolved);
        texture->rb_resolved = 0;
    }

    if (context) context_release(context);

    wined3d_texture_set_dirty(texture);

    resource_unload(&texture->resource);
}