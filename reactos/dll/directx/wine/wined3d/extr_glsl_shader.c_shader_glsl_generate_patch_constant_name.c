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
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_signature_element {int sysval_semantic; char const* semantic_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  WINED3D_SV_TESS_FACTOR_LINEDEN 133 
#define  WINED3D_SV_TESS_FACTOR_LINEDET 132 
#define  WINED3D_SV_TESS_FACTOR_QUADEDGE 131 
#define  WINED3D_SV_TESS_FACTOR_QUADINT 130 
#define  WINED3D_SV_TESS_FACTOR_TRIEDGE 129 
#define  WINED3D_SV_TESS_FACTOR_TRIINT 128 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char const*,...) ; 

__attribute__((used)) static void shader_glsl_generate_patch_constant_name(struct wined3d_string_buffer *buffer,
        const struct wined3d_shader_signature_element *constant, unsigned int *user_constant_idx,
        const char *reg_mask)
{
    if (!constant->sysval_semantic)
    {
        shader_addline(buffer, "user_patch_constant[%u]%s", (*user_constant_idx)++, reg_mask);
        return;
    }

    switch (constant->sysval_semantic)
    {
        case WINED3D_SV_TESS_FACTOR_QUADEDGE:
        case WINED3D_SV_TESS_FACTOR_TRIEDGE:
        case WINED3D_SV_TESS_FACTOR_LINEDET:
        case WINED3D_SV_TESS_FACTOR_LINEDEN:
            shader_addline(buffer, "gl_TessLevelOuter[%u]", constant->semantic_idx);
            break;
        case WINED3D_SV_TESS_FACTOR_QUADINT:
        case WINED3D_SV_TESS_FACTOR_TRIINT:
            shader_addline(buffer, "gl_TessLevelInner[%u]", constant->semantic_idx);
            break;
        default:
            FIXME("Unhandled sysval semantic %#x.\n", constant->sysval_semantic);
            shader_addline(buffer, "vec4(0.0)%s", reg_mask);
    }
}