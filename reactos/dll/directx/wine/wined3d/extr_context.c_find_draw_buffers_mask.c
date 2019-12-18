#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wined3d_state {struct wined3d_shader** shader; TYPE_1__* fb; } ;
struct TYPE_8__ {int rt_mask; } ;
struct wined3d_shader {TYPE_2__ reg_maps; } ;
struct wined3d_rendertarget_view {TYPE_4__* format; int /*<<< orphan*/  resource; } ;
struct wined3d_context {TYPE_3__* d3d_info; int /*<<< orphan*/  gl_info; int /*<<< orphan*/  render_offscreen; } ;
struct TYPE_12__ {int /*<<< orphan*/  container; } ;
struct TYPE_11__ {scalar_t__ offscreen_rendering_mode; } ;
struct TYPE_10__ {scalar_t__ id; } ;
struct TYPE_9__ {int valid_dual_rt_mask; int valid_rt_mask; } ;
struct TYPE_7__ {struct wined3d_rendertarget_view** render_targets; } ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ORM_FBO ; 
 scalar_t__ WINED3DFMT_NULL ; 
 size_t WINED3D_SHADER_TYPE_PIXEL ; 
 int context_generate_rt_mask_from_resource (int /*<<< orphan*/ ) ; 
 int context_generate_rt_mask_no_fbo (struct wined3d_context const*,int /*<<< orphan*/ ) ; 
 unsigned int wined3d_bit_scan (int*) ; 
 scalar_t__ wined3d_dualblend_enabled (struct wined3d_state const*,int /*<<< orphan*/ ) ; 
 TYPE_6__* wined3d_rendertarget_view_get_surface (struct wined3d_rendertarget_view* const) ; 
 TYPE_5__ wined3d_settings ; 

__attribute__((used)) static DWORD find_draw_buffers_mask(const struct wined3d_context *context, const struct wined3d_state *state)
{
    struct wined3d_rendertarget_view * const *rts = state->fb->render_targets;
    struct wined3d_shader *ps = state->shader[WINED3D_SHADER_TYPE_PIXEL];
    DWORD rt_mask, mask;
    unsigned int i;

    if (wined3d_settings.offscreen_rendering_mode != ORM_FBO)
        return context_generate_rt_mask_no_fbo(context, wined3d_rendertarget_view_get_surface(rts[0])->container);
    else if (!context->render_offscreen)
        return context_generate_rt_mask_from_resource(rts[0]->resource);

    /* If we attach more buffers than supported in dual blend mode, the NVIDIA
     * driver generates the following error:
     *      GL_INVALID_OPERATION error generated. State(s) are invalid: blend.
     * DX11 does not treat this configuration as invalid, so disable the unused ones.
     */
    rt_mask = ps ? ps->reg_maps.rt_mask : 1;
    if (wined3d_dualblend_enabled(state, context->gl_info))
        rt_mask &= context->d3d_info->valid_dual_rt_mask;
    else
        rt_mask &= context->d3d_info->valid_rt_mask;

    mask = rt_mask;
    i = 0;
    while (mask)
    {
        i = wined3d_bit_scan(&mask);
        if (!rts[i] || rts[i]->format->id == WINED3DFMT_NULL)
            rt_mask &= ~(1u << i);
    }

    return rt_mask;
}