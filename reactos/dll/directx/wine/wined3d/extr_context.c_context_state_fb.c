#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct wined3d_state {struct wined3d_fb_state* fb; } ;
struct wined3d_fb_state {TYPE_8__* depth_stencil; TYPE_4__** render_targets; } ;
struct wined3d_context {scalar_t__ draw_buffers_mask; int /*<<< orphan*/  constant_update_mask; TYPE_6__* current_fbo; TYPE_9__* blit_targets; TYPE_2__* gl_info; int /*<<< orphan*/  render_offscreen; } ;
struct TYPE_19__ {int /*<<< orphan*/  layer_count; int /*<<< orphan*/  sub_resource_idx; TYPE_3__* resource; int /*<<< orphan*/  gl_view; } ;
struct TYPE_18__ {TYPE_5__* resource; } ;
struct TYPE_17__ {scalar_t__ offscreen_rendering_mode; } ;
struct TYPE_16__ {scalar_t__ rt_mask; } ;
struct TYPE_15__ {scalar_t__ draw_binding; } ;
struct TYPE_14__ {TYPE_3__* resource; int /*<<< orphan*/  layer_count; int /*<<< orphan*/  sub_resource_idx; int /*<<< orphan*/  gl_view; } ;
struct TYPE_13__ {scalar_t__ draw_binding; } ;
struct TYPE_11__ {unsigned int buffers; } ;
struct TYPE_12__ {TYPE_1__ limits; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FRAMEBUFFER ; 
 scalar_t__ ORM_FBO ; 
 scalar_t__ WINED3D_LOCATION_DRAWABLE ; 
 int /*<<< orphan*/  WINED3D_SHADER_CONST_PS_Y_CORR ; 
 int /*<<< orphan*/  context_apply_draw_buffers (struct wined3d_context*,scalar_t__) ; 
 int /*<<< orphan*/  context_apply_fbo_state (struct wined3d_context*,int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ find_draw_buffers_mask (struct wined3d_context*,struct wined3d_state const*) ; 
 int /*<<< orphan*/  memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * wined3d_rendertarget_view_get_surface (TYPE_8__*) ; 
 TYPE_7__ wined3d_settings ; 

void context_state_fb(struct wined3d_context *context, const struct wined3d_state *state, DWORD state_id)
{
    DWORD rt_mask = find_draw_buffers_mask(context, state);
    const struct wined3d_fb_state *fb = state->fb;
    DWORD color_location = 0;
    DWORD *cur_mask;

    if (wined3d_settings.offscreen_rendering_mode == ORM_FBO)
    {
        if (!context->render_offscreen)
        {
            context_apply_fbo_state(context, GL_FRAMEBUFFER, NULL, NULL,
                    WINED3D_LOCATION_DRAWABLE, WINED3D_LOCATION_DRAWABLE);
        }
        else
        {
            unsigned int i;

            memset(context->blit_targets, 0, sizeof(context->blit_targets));
            for (i = 0; i < context->gl_info->limits.buffers; ++i)
            {
                if (!fb->render_targets[i])
                    continue;

                context->blit_targets[i].gl_view = fb->render_targets[i]->gl_view;
                context->blit_targets[i].resource = fb->render_targets[i]->resource;
                context->blit_targets[i].sub_resource_idx = fb->render_targets[i]->sub_resource_idx;
                context->blit_targets[i].layer_count = fb->render_targets[i]->layer_count;

                if (!color_location)
                    color_location = fb->render_targets[i]->resource->draw_binding;
            }
            context_apply_fbo_state(context, GL_FRAMEBUFFER, context->blit_targets,
                    wined3d_rendertarget_view_get_surface(fb->depth_stencil),
                    color_location, fb->depth_stencil ? fb->depth_stencil->resource->draw_binding : 0);
        }
    }

    cur_mask = context->current_fbo ? &context->current_fbo->rt_mask : &context->draw_buffers_mask;
    if (rt_mask != *cur_mask)
    {
        context_apply_draw_buffers(context, rt_mask);
        *cur_mask = rt_mask;
    }
    context->constant_update_mask |= WINED3D_SHADER_CONST_PS_Y_CORR;
}