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
struct wined3d_state {scalar_t__* render_states; } ;
struct TYPE_2__ {scalar_t__ position_transformed; } ;
struct wined3d_context {unsigned int shader_update_mask; int fog_source; int /*<<< orphan*/  constant_update_mask; TYPE_1__ stream_info; } ;
typedef  enum fogsource { ____Placeholder_fogsource } fogsource ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int FOGSOURCE_COORD ; 
 int FOGSOURCE_FFP ; 
 int FOGSOURCE_VS ; 
 scalar_t__ WINED3D_FOG_NONE ; 
 size_t WINED3D_RS_FOGENABLE ; 
 size_t WINED3D_RS_FOGEND ; 
 size_t WINED3D_RS_FOGSTART ; 
 size_t WINED3D_RS_FOGTABLEMODE ; 
 size_t WINED3D_RS_FOGVERTEXMODE ; 
 int /*<<< orphan*/  WINED3D_SHADER_CONST_PS_FOG ; 
 unsigned int WINED3D_SHADER_TYPE_PIXEL ; 
 scalar_t__ use_vs (struct wined3d_state const*) ; 

__attribute__((used)) static void glsl_fragment_pipe_fog(struct wined3d_context *context,
        const struct wined3d_state *state, DWORD state_id)
{
    BOOL use_vshader = use_vs(state);
    enum fogsource new_source;
    DWORD fogstart = state->render_states[WINED3D_RS_FOGSTART];
    DWORD fogend = state->render_states[WINED3D_RS_FOGEND];

    context->shader_update_mask |= 1u << WINED3D_SHADER_TYPE_PIXEL;

    if (!state->render_states[WINED3D_RS_FOGENABLE])
        return;

    if (state->render_states[WINED3D_RS_FOGTABLEMODE] == WINED3D_FOG_NONE)
    {
        if (use_vshader)
            new_source = FOGSOURCE_VS;
        else if (state->render_states[WINED3D_RS_FOGVERTEXMODE] == WINED3D_FOG_NONE || context->stream_info.position_transformed)
            new_source = FOGSOURCE_COORD;
        else
            new_source = FOGSOURCE_FFP;
    }
    else
    {
        new_source = FOGSOURCE_FFP;
    }

    if (new_source != context->fog_source || fogstart == fogend)
    {
        context->fog_source = new_source;
        context->constant_update_mask |= WINED3D_SHADER_CONST_PS_FOG;
    }
}