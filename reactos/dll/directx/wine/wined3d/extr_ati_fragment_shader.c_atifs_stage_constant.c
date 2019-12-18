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
struct wined3d_state {int /*<<< orphan*/ ** texture_states; } ;
struct wined3d_gl_info {int dummy; } ;
struct wined3d_context {struct atifs_context_private_data* fragment_pipe_data; struct wined3d_gl_info* gl_info; } ;
struct wined3d_color {int /*<<< orphan*/  r; } ;
struct atifs_context_private_data {TYPE_1__* last_shader; } ;
struct TYPE_2__ {scalar_t__* constants; } ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ATIFS_CONSTANT_STAGE ; 
 int /*<<< orphan*/  ATIFS_CONST_STAGE (int) ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int STATE_TEXTURESTAGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WINED3D_HIGHEST_TEXTURE_STATE ; 
 size_t WINED3D_TSS_CONSTANT ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glSetFragmentShaderConstantATI (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wined3d_color_from_d3dcolor (struct wined3d_color*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atifs_stage_constant(struct wined3d_context *context, const struct wined3d_state *state, DWORD state_id)
{
    DWORD stage = (state_id - STATE_TEXTURESTAGE(0, 0)) / (WINED3D_HIGHEST_TEXTURE_STATE + 1);
    const struct wined3d_gl_info *gl_info = context->gl_info;
    struct atifs_context_private_data *ctx_priv = context->fragment_pipe_data;
    struct wined3d_color color;

    if (!ctx_priv->last_shader
            || ctx_priv->last_shader->constants[stage] != ATIFS_CONSTANT_STAGE)
        return;

    wined3d_color_from_d3dcolor(&color, state->texture_states[stage][WINED3D_TSS_CONSTANT]);
    GL_EXTCALL(glSetFragmentShaderConstantATI(ATIFS_CONST_STAGE(stage), &color.r));
    checkGLcall("glSetFragmentShaderConstantATI(ATIFS_CONST_STAGE(stage), &color.r)");
}