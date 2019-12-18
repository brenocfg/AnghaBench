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
struct wined3d_state {scalar_t__** texture_states; int /*<<< orphan*/ * textures; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* p_glTexEnvi ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glDisable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glEnable ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_2__ gl; } ;
struct TYPE_4__ {int textures; } ;
struct wined3d_gl_info {scalar_t__* supported; TYPE_3__ gl_ops; TYPE_1__ limits; } ;
struct wined3d_context {unsigned int fixed_function_usage_map; int* tex_unit_map; int lowest_disabled_stage; unsigned int texShaderBumpMap; struct wined3d_gl_info* gl_info; } ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 size_t ARB_TEXTURE_CUBE_MAP ; 
 size_t ARB_TEXTURE_RECTANGLE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_NONE ; 
 int /*<<< orphan*/  GL_NUM_GENERAL_COMBINERS_NV ; 
 int /*<<< orphan*/  GL_REGISTER_COMBINERS_NV ; 
 int /*<<< orphan*/  GL_SHADER_OPERATION_NV ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_3D ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_ARB ; 
 int /*<<< orphan*/  GL_TEXTURE_RECTANGLE_ARB ; 
 int /*<<< orphan*/  GL_TEXTURE_SHADER_NV ; 
 size_t NV_TEXTURE_SHADER2 ; 
 int /*<<< orphan*/  STATE_SAMPLER (int) ; 
 int STATE_TEXTURESTAGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*,int,int) ; 
 int WINED3D_HIGHEST_TEXTURE_STATE ; 
 scalar_t__ WINED3D_TOP_BUMPENVMAP ; 
 scalar_t__ WINED3D_TOP_BUMPENVMAP_LUMINANCE ; 
 size_t WINED3D_TSS_COLOR_ARG0 ; 
 size_t WINED3D_TSS_COLOR_ARG1 ; 
 size_t WINED3D_TSS_COLOR_ARG2 ; 
 size_t WINED3D_TSS_COLOR_OP ; 
 size_t WINED3D_TSS_RESULT_ARG ; 
 int WINED3D_UNMAPPED_STAGE ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  context_active_texture (struct wined3d_context*,struct wined3d_gl_info const*,int) ; 
 int /*<<< orphan*/  glCombinerParameteriNV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isStateDirty (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvts_activate_dimensions (struct wined3d_state const*,int,struct wined3d_context*) ; 
 int /*<<< orphan*/  set_tex_op_nvrc (struct wined3d_gl_info const*,struct wined3d_state const*,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  texture_activate_dimensions (int /*<<< orphan*/ ,struct wined3d_gl_info const*) ; 
 scalar_t__ use_ps (struct wined3d_state const*) ; 

__attribute__((used)) static void nvrc_colorop(struct wined3d_context *context, const struct wined3d_state *state, DWORD state_id)
{
    DWORD stage = (state_id - STATE_TEXTURESTAGE(0, 0)) / (WINED3D_HIGHEST_TEXTURE_STATE + 1);
    BOOL tex_used = context->fixed_function_usage_map & (1u << stage);
    DWORD mapped_stage = context->tex_unit_map[stage];
    const struct wined3d_gl_info *gl_info = context->gl_info;

    TRACE("Setting color op for stage %u.\n", stage);

    /* Using a pixel shader? Don't care for anything here, the shader applying does it */
    if (use_ps(state)) return;

    if (stage != mapped_stage) WARN("Using non 1:1 mapping: %d -> %d!\n", stage, mapped_stage);

    if (mapped_stage != WINED3D_UNMAPPED_STAGE)
    {
        if (tex_used && mapped_stage >= gl_info->limits.textures)
        {
            FIXME("Attempt to enable unsupported stage!\n");
            return;
        }
        context_active_texture(context, gl_info, mapped_stage);
    }

    if (context->lowest_disabled_stage > 0)
    {
        gl_info->gl_ops.gl.p_glEnable(GL_REGISTER_COMBINERS_NV);
        GL_EXTCALL(glCombinerParameteriNV(GL_NUM_GENERAL_COMBINERS_NV, context->lowest_disabled_stage));
    }
    else
    {
        gl_info->gl_ops.gl.p_glDisable(GL_REGISTER_COMBINERS_NV);
    }
    if (stage >= context->lowest_disabled_stage)
    {
        TRACE("Stage disabled\n");
        if (mapped_stage != WINED3D_UNMAPPED_STAGE)
        {
            /* Disable everything here */
            gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_2D);
            checkGLcall("glDisable(GL_TEXTURE_2D)");
            gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_3D);
            checkGLcall("glDisable(GL_TEXTURE_3D)");
            if (gl_info->supported[ARB_TEXTURE_CUBE_MAP])
            {
                gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_CUBE_MAP_ARB);
                checkGLcall("glDisable(GL_TEXTURE_CUBE_MAP_ARB)");
            }
            if (gl_info->supported[ARB_TEXTURE_RECTANGLE])
            {
                gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_RECTANGLE_ARB);
                checkGLcall("glDisable(GL_TEXTURE_RECTANGLE_ARB)");
            }
            if (gl_info->supported[NV_TEXTURE_SHADER2] && mapped_stage < gl_info->limits.textures)
            {
                gl_info->gl_ops.gl.p_glTexEnvi(GL_TEXTURE_SHADER_NV, GL_SHADER_OPERATION_NV, GL_NONE);
            }
        }
        /* All done */
        return;
    }

    /* The sampler will also activate the correct texture dimensions, so no need to do it here
     * if the sampler for this stage is dirty
     */
    if (!isStateDirty(context, STATE_SAMPLER(stage)))
    {
        if (tex_used)
        {
            if (gl_info->supported[NV_TEXTURE_SHADER2])
            {
                nvts_activate_dimensions(state, stage, context);
            }
            else
            {
                texture_activate_dimensions(state->textures[stage], gl_info);
            }
        }
    }

    /* Set the texture combiners */
    set_tex_op_nvrc(gl_info, state, FALSE, stage,
            state->texture_states[stage][WINED3D_TSS_COLOR_OP],
            state->texture_states[stage][WINED3D_TSS_COLOR_ARG1],
            state->texture_states[stage][WINED3D_TSS_COLOR_ARG2],
            state->texture_states[stage][WINED3D_TSS_COLOR_ARG0],
            mapped_stage,
            state->texture_states[stage][WINED3D_TSS_RESULT_ARG]);

    /* In register combiners bump mapping is done in the stage AFTER the one that has the bump map operation set,
     * thus the texture shader may have to be updated
     */
    if (gl_info->supported[NV_TEXTURE_SHADER2])
    {
        BOOL usesBump = (state->texture_states[stage][WINED3D_TSS_COLOR_OP] == WINED3D_TOP_BUMPENVMAP_LUMINANCE
                || state->texture_states[stage][WINED3D_TSS_COLOR_OP] == WINED3D_TOP_BUMPENVMAP);
        BOOL usedBump = !!(context->texShaderBumpMap & 1u << (stage + 1));
        if (usesBump != usedBump)
        {
            context_active_texture(context, gl_info, mapped_stage + 1);
            nvts_activate_dimensions(state, stage + 1, context);
            context_active_texture(context, gl_info, mapped_stage);
        }
    }
}