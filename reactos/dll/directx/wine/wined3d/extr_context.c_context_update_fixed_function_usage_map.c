#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wined3d_state {int** texture_states; } ;
struct wined3d_context {unsigned int fixed_function_usage_map; size_t lowest_disabled_stage; } ;
typedef  enum wined3d_texture_op { ____Placeholder_wined3d_texture_op } wined3d_texture_op ;
typedef  size_t UINT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 size_t MAX_TEXTURES ; 
 int /*<<< orphan*/  STATE_TEXTURESTAGE (size_t,size_t) ; 
 scalar_t__ WINED3DTA_SELECTMASK ; 
 scalar_t__ WINED3DTA_TEXTURE ; 
 int WINED3D_TOP_BUMPENVMAP ; 
 int WINED3D_TOP_BUMPENVMAP_LUMINANCE ; 
 int WINED3D_TOP_DISABLE ; 
 int WINED3D_TOP_LERP ; 
 int WINED3D_TOP_MULTIPLY_ADD ; 
 int WINED3D_TOP_SELECT_ARG1 ; 
 int WINED3D_TOP_SELECT_ARG2 ; 
 size_t WINED3D_TSS_ALPHA_ARG0 ; 
 size_t WINED3D_TSS_ALPHA_ARG1 ; 
 size_t WINED3D_TSS_ALPHA_ARG2 ; 
 size_t WINED3D_TSS_ALPHA_OP ; 
 size_t WINED3D_TSS_COLOR_ARG0 ; 
 size_t WINED3D_TSS_COLOR_ARG1 ; 
 size_t WINED3D_TSS_COLOR_ARG2 ; 
 size_t WINED3D_TSS_COLOR_OP ; 
 int /*<<< orphan*/  context_invalidate_state (struct wined3d_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void context_update_fixed_function_usage_map(struct wined3d_context *context,
        const struct wined3d_state *state)
{
    UINT i, start, end;

    context->fixed_function_usage_map = 0;
    for (i = 0; i < MAX_TEXTURES; ++i)
    {
        enum wined3d_texture_op color_op = state->texture_states[i][WINED3D_TSS_COLOR_OP];
        enum wined3d_texture_op alpha_op = state->texture_states[i][WINED3D_TSS_ALPHA_OP];
        DWORD color_arg1 = state->texture_states[i][WINED3D_TSS_COLOR_ARG1] & WINED3DTA_SELECTMASK;
        DWORD color_arg2 = state->texture_states[i][WINED3D_TSS_COLOR_ARG2] & WINED3DTA_SELECTMASK;
        DWORD color_arg3 = state->texture_states[i][WINED3D_TSS_COLOR_ARG0] & WINED3DTA_SELECTMASK;
        DWORD alpha_arg1 = state->texture_states[i][WINED3D_TSS_ALPHA_ARG1] & WINED3DTA_SELECTMASK;
        DWORD alpha_arg2 = state->texture_states[i][WINED3D_TSS_ALPHA_ARG2] & WINED3DTA_SELECTMASK;
        DWORD alpha_arg3 = state->texture_states[i][WINED3D_TSS_ALPHA_ARG0] & WINED3DTA_SELECTMASK;

        /* Not used, and disable higher stages. */
        if (color_op == WINED3D_TOP_DISABLE)
            break;

        if (((color_arg1 == WINED3DTA_TEXTURE) && color_op != WINED3D_TOP_SELECT_ARG2)
                || ((color_arg2 == WINED3DTA_TEXTURE) && color_op != WINED3D_TOP_SELECT_ARG1)
                || ((color_arg3 == WINED3DTA_TEXTURE)
                    && (color_op == WINED3D_TOP_MULTIPLY_ADD || color_op == WINED3D_TOP_LERP))
                || ((alpha_arg1 == WINED3DTA_TEXTURE) && alpha_op != WINED3D_TOP_SELECT_ARG2)
                || ((alpha_arg2 == WINED3DTA_TEXTURE) && alpha_op != WINED3D_TOP_SELECT_ARG1)
                || ((alpha_arg3 == WINED3DTA_TEXTURE)
                    && (alpha_op == WINED3D_TOP_MULTIPLY_ADD || alpha_op == WINED3D_TOP_LERP)))
            context->fixed_function_usage_map |= (1u << i);

        if ((color_op == WINED3D_TOP_BUMPENVMAP || color_op == WINED3D_TOP_BUMPENVMAP_LUMINANCE)
                && i < MAX_TEXTURES - 1)
            context->fixed_function_usage_map |= (1u << (i + 1));
    }

    if (i < context->lowest_disabled_stage)
    {
        start = i;
        end = context->lowest_disabled_stage;
    }
    else
    {
        start = context->lowest_disabled_stage;
        end = i;
    }

    context->lowest_disabled_stage = i;
    for (i = start + 1; i < end; ++i)
    {
        context_invalidate_state(context, STATE_TEXTURESTAGE(i, WINED3D_TSS_COLOR_OP));
    }
}