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
struct wined3d_state {int dummy; } ;
struct TYPE_2__ {unsigned int user_clip_distances; } ;
struct wined3d_gl_info {TYPE_1__ limits; } ;
struct wined3d_context {int constant_update_mask; struct wined3d_gl_info* gl_info; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_CLIPPLANE (unsigned int) ; 
 int WINED3D_SHADER_CONST_FFP_LIGHTS ; 
 int WINED3D_SHADER_CONST_FFP_MODELVIEW ; 
 int WINED3D_SHADER_CONST_FFP_VERTEXBLEND ; 
 int WINED3D_SHADER_CONST_VS_CLIP_PLANES ; 
 int /*<<< orphan*/  clipplane (struct wined3d_context*,struct wined3d_state const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isStateDirty (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 scalar_t__ needs_legacy_glsl_syntax (struct wined3d_gl_info const*) ; 

__attribute__((used)) static void glsl_vertex_pipe_view(struct wined3d_context *context, const struct wined3d_state *state, DWORD state_id)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    unsigned int k;

    context->constant_update_mask |= WINED3D_SHADER_CONST_FFP_MODELVIEW
            | WINED3D_SHADER_CONST_FFP_LIGHTS
            | WINED3D_SHADER_CONST_FFP_VERTEXBLEND;

    if (needs_legacy_glsl_syntax(gl_info))
    {
        for (k = 0; k < gl_info->limits.user_clip_distances; ++k)
        {
            if (!isStateDirty(context, STATE_CLIPPLANE(k)))
                clipplane(context, state, STATE_CLIPPLANE(k));
        }
    }
    else
    {
        context->constant_update_mask |= WINED3D_SHADER_CONST_VS_CLIP_PLANES;
    }
}