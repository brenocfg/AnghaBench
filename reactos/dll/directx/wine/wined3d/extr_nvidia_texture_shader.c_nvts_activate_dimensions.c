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
struct wined3d_state {scalar_t__** texture_states; TYPE_1__** textures; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* p_glTexEnvi ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ;} ;
struct TYPE_6__ {TYPE_2__ gl; } ;
struct wined3d_gl_info {TYPE_3__ gl_ops; } ;
struct wined3d_context {unsigned int texShaderBumpMap; struct wined3d_gl_info* gl_info; } ;
struct TYPE_4__ {int target; } ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int const GL_NONE ; 
 int const GL_OFFSET_TEXTURE_2D_NV ; 
 int /*<<< orphan*/  GL_SHADER_OPERATION_NV ; 
#define  GL_TEXTURE_2D 131 
#define  GL_TEXTURE_3D 130 
#define  GL_TEXTURE_CUBE_MAP_ARB 129 
#define  GL_TEXTURE_RECTANGLE_ARB 128 
 int /*<<< orphan*/  GL_TEXTURE_SHADER_NV ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WINED3D_TOP_BUMPENVMAP ; 
 scalar_t__ WINED3D_TOP_BUMPENVMAP_LUMINANCE ; 
 size_t WINED3D_TSS_COLOR_OP ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void nvts_activate_dimensions(const struct wined3d_state *state, DWORD stage, struct wined3d_context *context)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    BOOL bumpmap = FALSE;

    if (stage > 0
            && (state->texture_states[stage - 1][WINED3D_TSS_COLOR_OP] == WINED3D_TOP_BUMPENVMAP_LUMINANCE
            || state->texture_states[stage - 1][WINED3D_TSS_COLOR_OP] == WINED3D_TOP_BUMPENVMAP))
    {
        bumpmap = TRUE;
        context->texShaderBumpMap |= (1u << stage);
    }
    else
    {
        context->texShaderBumpMap &= ~(1u << stage);
    }

    if (state->textures[stage])
    {
        switch (state->textures[stage]->target)
        {
            case GL_TEXTURE_2D:
                gl_info->gl_ops.gl.p_glTexEnvi(GL_TEXTURE_SHADER_NV, GL_SHADER_OPERATION_NV,
                        bumpmap ? GL_OFFSET_TEXTURE_2D_NV : GL_TEXTURE_2D);
                checkGLcall("glTexEnvi(GL_TEXTURE_SHADER_NV, GL_SHADER_OPERATION_NV, ...)");
                break;
            case GL_TEXTURE_RECTANGLE_ARB:
                gl_info->gl_ops.gl.p_glTexEnvi(GL_TEXTURE_SHADER_NV, GL_SHADER_OPERATION_NV,
                        bumpmap ? GL_OFFSET_TEXTURE_2D_NV : GL_TEXTURE_RECTANGLE_ARB);
                checkGLcall("glTexEnvi(GL_TEXTURE_SHADER_NV, GL_SHADER_OPERATION_NV, ...)");
                break;
            case GL_TEXTURE_3D:
                gl_info->gl_ops.gl.p_glTexEnvi(GL_TEXTURE_SHADER_NV, GL_SHADER_OPERATION_NV, GL_TEXTURE_3D);
                checkGLcall("glTexEnvi(GL_TEXTURE_SHADER_NV, GL_SHADER_OPERATION_NV, GL_TEXTURE_3D)");
                break;
            case GL_TEXTURE_CUBE_MAP_ARB:
                gl_info->gl_ops.gl.p_glTexEnvi(GL_TEXTURE_SHADER_NV, GL_SHADER_OPERATION_NV, GL_TEXTURE_CUBE_MAP_ARB);
                checkGLcall("glTexEnvi(GL_TEXTURE_SHADER_NV, GL_SHADER_OPERATION_NV, GL_TEXTURE_CUBE_MAP_ARB)");
                break;
        }
    }
    else
    {
        gl_info->gl_ops.gl.p_glTexEnvi(GL_TEXTURE_SHADER_NV, GL_SHADER_OPERATION_NV, GL_NONE);
        checkGLcall("glTexEnvi(GL_TEXTURE_SHADER_NV, GL_SHADER_OPERATION_NV, GL_NONE)");
    }
}