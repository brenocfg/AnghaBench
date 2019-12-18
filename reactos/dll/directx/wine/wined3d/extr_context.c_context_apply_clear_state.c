#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct wined3d_state {struct wined3d_fb_state const* fb; } ;
struct wined3d_rendertarget_view {TYPE_2__* format; TYPE_7__* resource; int /*<<< orphan*/  layer_count; int /*<<< orphan*/  sub_resource_idx; int /*<<< orphan*/  gl_view; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* p_glDisable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glEnable ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_17__ {TYPE_4__ gl; } ;
struct TYPE_13__ {unsigned int buffers; } ;
struct wined3d_gl_info {TYPE_5__ gl_ops; scalar_t__* supported; TYPE_1__ limits; } ;
struct wined3d_fb_state {struct wined3d_rendertarget_view* depth_stencil; struct wined3d_rendertarget_view** render_targets; } ;
struct wined3d_context {unsigned int draw_buffers_mask; int /*<<< orphan*/  last_was_blit; TYPE_3__* current_fbo; TYPE_9__* blit_targets; struct wined3d_gl_info* gl_info; } ;
typedef  unsigned int UINT ;
struct TYPE_21__ {int /*<<< orphan*/  layer_count; int /*<<< orphan*/  sub_resource_idx; TYPE_7__* resource; int /*<<< orphan*/  gl_view; } ;
struct TYPE_20__ {int /*<<< orphan*/ * container; } ;
struct TYPE_19__ {int /*<<< orphan*/  draw_binding; } ;
struct TYPE_18__ {scalar_t__ offscreen_rendering_mode; } ;
struct TYPE_15__ {unsigned int rt_mask; } ;
struct TYPE_14__ {scalar_t__ id; } ;
typedef  unsigned int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t ARB_FRAMEBUFFER_SRGB ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_FRAMEBUFFER_SRGB ; 
 int /*<<< orphan*/  GL_SCISSOR_TEST ; 
 scalar_t__ ORM_FBO ; 
 int /*<<< orphan*/  STATE_FRAMEBUFFER ; 
 int /*<<< orphan*/  STATE_RENDER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_SCISSORRECT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 scalar_t__ WINED3DFMT_NULL ; 
 int /*<<< orphan*/  WINED3D_LOCATION_DRAWABLE ; 
 int /*<<< orphan*/  WINED3D_RS_ALPHABLENDENABLE ; 
 int /*<<< orphan*/  WINED3D_RS_SCISSORTESTENABLE ; 
 int /*<<< orphan*/  WINED3D_RS_SRGBWRITEENABLE ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  context_apply_draw_buffers (struct wined3d_context*,unsigned int) ; 
 int /*<<< orphan*/  context_apply_fbo_state (struct wined3d_context*,int /*<<< orphan*/ ,TYPE_9__*,TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_check_fbo_status (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 unsigned int context_generate_rt_mask_from_resource (TYPE_7__*) ; 
 unsigned int context_generate_rt_mask_no_fbo (struct wined3d_context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  context_invalidate_state (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_validate_onscreen_formats (struct wined3d_context*,struct wined3d_rendertarget_view*) ; 
 int /*<<< orphan*/  have_framebuffer_attachment (unsigned int,struct wined3d_rendertarget_view* const*,struct wined3d_rendertarget_view*) ; 
 scalar_t__ isStateDirty (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ needs_srgb_write (struct wined3d_context*,struct wined3d_state const*,struct wined3d_fb_state const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 TYPE_8__* wined3d_rendertarget_view_get_surface (struct wined3d_rendertarget_view* const) ; 
 scalar_t__ wined3d_resource_is_offscreen (TYPE_7__*) ; 
 TYPE_6__ wined3d_settings ; 

BOOL context_apply_clear_state(struct wined3d_context *context, const struct wined3d_state *state,
        UINT rt_count, const struct wined3d_fb_state *fb)
{
    struct wined3d_rendertarget_view * const *rts = fb->render_targets;
    struct wined3d_rendertarget_view *dsv = fb->depth_stencil;
    const struct wined3d_gl_info *gl_info = context->gl_info;
    DWORD rt_mask = 0, *cur_mask;
    unsigned int i;

    if (isStateDirty(context, STATE_FRAMEBUFFER) || fb != state->fb
            || rt_count != gl_info->limits.buffers)
    {
        if (!have_framebuffer_attachment(rt_count, rts, dsv))
        {
            WARN("Invalid render target config, need at least one attachment.\n");
            return FALSE;
        }

        if (wined3d_settings.offscreen_rendering_mode == ORM_FBO)
        {
            context_validate_onscreen_formats(context, dsv);

            if (!rt_count || wined3d_resource_is_offscreen(rts[0]->resource))
            {
                memset(context->blit_targets, 0, sizeof(context->blit_targets));
                for (i = 0; i < rt_count; ++i)
                {
                    if (rts[i])
                    {
                        context->blit_targets[i].gl_view = rts[i]->gl_view;
                        context->blit_targets[i].resource = rts[i]->resource;
                        context->blit_targets[i].sub_resource_idx = rts[i]->sub_resource_idx;
                        context->blit_targets[i].layer_count = rts[i]->layer_count;
                    }
                    if (rts[i] && rts[i]->format->id != WINED3DFMT_NULL)
                        rt_mask |= (1u << i);
                }
                context_apply_fbo_state(context, GL_FRAMEBUFFER, context->blit_targets,
                        wined3d_rendertarget_view_get_surface(dsv),
                        rt_count ? rts[0]->resource->draw_binding : 0,
                        dsv ? dsv->resource->draw_binding : 0);
            }
            else
            {
                context_apply_fbo_state(context, GL_FRAMEBUFFER, NULL, NULL,
                        WINED3D_LOCATION_DRAWABLE, WINED3D_LOCATION_DRAWABLE);
                rt_mask = context_generate_rt_mask_from_resource(rts[0]->resource);
            }

            /* If the framebuffer is not the device's fb the device's fb has to be reapplied
             * next draw. Otherwise we could mark the framebuffer state clean here, once the
             * state management allows this */
            context_invalidate_state(context, STATE_FRAMEBUFFER);
        }
        else
        {
            rt_mask = context_generate_rt_mask_no_fbo(context,
                    rt_count ? wined3d_rendertarget_view_get_surface(rts[0])->container : NULL);
        }
    }
    else if (wined3d_settings.offscreen_rendering_mode == ORM_FBO
            && (!rt_count || wined3d_resource_is_offscreen(rts[0]->resource)))
    {
        for (i = 0; i < rt_count; ++i)
        {
            if (rts[i] && rts[i]->format->id != WINED3DFMT_NULL)
                rt_mask |= (1u << i);
        }
    }
    else
    {
        rt_mask = context_generate_rt_mask_no_fbo(context,
                rt_count ? wined3d_rendertarget_view_get_surface(rts[0])->container : NULL);
    }

    cur_mask = context->current_fbo ? &context->current_fbo->rt_mask : &context->draw_buffers_mask;

    if (rt_mask != *cur_mask)
    {
        context_apply_draw_buffers(context, rt_mask);
        *cur_mask = rt_mask;
        context_invalidate_state(context, STATE_FRAMEBUFFER);
    }

    if (wined3d_settings.offscreen_rendering_mode == ORM_FBO)
    {
        context_check_fbo_status(context, GL_FRAMEBUFFER);
    }

    context->last_was_blit = FALSE;

    /* Blending and clearing should be orthogonal, but tests on the nvidia
     * driver show that disabling blending when clearing improves the clearing
     * performance incredibly. */
    gl_info->gl_ops.gl.p_glDisable(GL_BLEND);
    gl_info->gl_ops.gl.p_glEnable(GL_SCISSOR_TEST);
    if (rt_count && gl_info->supported[ARB_FRAMEBUFFER_SRGB])
    {
        if (needs_srgb_write(context, state, fb))
            gl_info->gl_ops.gl.p_glEnable(GL_FRAMEBUFFER_SRGB);
        else
            gl_info->gl_ops.gl.p_glDisable(GL_FRAMEBUFFER_SRGB);
        context_invalidate_state(context, STATE_RENDER(WINED3D_RS_SRGBWRITEENABLE));
    }
    checkGLcall("setting up state for clear");

    context_invalidate_state(context, STATE_RENDER(WINED3D_RS_ALPHABLENDENABLE));
    context_invalidate_state(context, STATE_RENDER(WINED3D_RS_SCISSORTESTENABLE));
    context_invalidate_state(context, STATE_SCISSORRECT);

    return TRUE;
}