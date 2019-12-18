#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_instruction {scalar_t__ handler_idx; int /*<<< orphan*/ * src; struct wined3d_shader_dst_param* dst; TYPE_1__* ctx; } ;
struct TYPE_8__ {TYPE_2__* idx; } ;
struct wined3d_shader_dst_param {TYPE_3__ reg; } ;
struct shader_arb_ctx_priv {TYPE_5__* cur_ps_args; } ;
struct TYPE_9__ {int tex_transform; } ;
struct TYPE_10__ {TYPE_4__ super; } ;
struct TYPE_7__ {int offset; } ;
struct TYPE_6__ {struct wined3d_string_buffer* buffer; struct shader_arb_ctx_priv* backend_data; } ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ WINED3DSIH_TEXBEML ; 
 int WINED3D_PSARGS_PROJECTED ; 
 int WINED3D_PSARGS_TEXTRANSFORM_SHIFT ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_arb_get_dst_param (struct wined3d_shader_instruction const*,struct wined3d_shader_dst_param*,char*) ; 
 int /*<<< orphan*/  shader_arb_get_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shader_hw_sample (struct wined3d_shader_instruction const*,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void pshader_hw_texbem(const struct wined3d_shader_instruction *ins)
{
    struct shader_arb_ctx_priv *priv = ins->ctx->backend_data;
    const struct wined3d_shader_dst_param *dst = &ins->dst[0];
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    char reg_coord[40], dst_reg[50], src_reg[50];
    DWORD reg_dest_code;

    /* All versions have a destination register. The Tx where the texture coordinates come
     * from is the varying incarnation of the texture register
     */
    reg_dest_code = dst->reg.idx[0].offset;
    shader_arb_get_dst_param(ins, &ins->dst[0], dst_reg);
    shader_arb_get_src_param(ins, &ins->src[0], 0, src_reg);
    sprintf(reg_coord, "fragment.texcoord[%u]", reg_dest_code);

    /* Sampling the perturbation map in Tsrc was done already, including the signedness correction if needed
     * The Tx in which the perturbation map is stored is the tempreg incarnation of the texture register
     *
     * GL_NV_fragment_program_option could handle this in one instruction via X2D:
     * X2D TA.xy, fragment.texcoord, T%u, bumpenvmat%u.xzyw
     *
     * However, the NV extensions are never enabled for <= 2.0 shaders because of the performance penalty that
     * comes with it, and texbem is an 1.x only instruction. No 1.x instruction forces us to enable the NV
     * extension.
     */
    shader_addline(buffer, "SWZ TB, bumpenvmat%d, x, z, 0, 0;\n", reg_dest_code);
    shader_addline(buffer, "DP3 TA.x, TB, %s;\n", src_reg);
    shader_addline(buffer, "SWZ TB, bumpenvmat%d, y, w, 0, 0;\n", reg_dest_code);
    shader_addline(buffer, "DP3 TA.y, TB, %s;\n", src_reg);

    /* with projective textures, texbem only divides the static texture coord, not the displacement,
     * so we can't let the GL handle this.
     */
    if ((priv->cur_ps_args->super.tex_transform >> reg_dest_code * WINED3D_PSARGS_TEXTRANSFORM_SHIFT)
            & WINED3D_PSARGS_PROJECTED)
    {
        shader_addline(buffer, "RCP TB.w, %s.w;\n", reg_coord);
        shader_addline(buffer, "MUL TB.xy, %s, TB.w;\n", reg_coord);
        shader_addline(buffer, "ADD TA.xy, TA, TB;\n");
    } else {
        shader_addline(buffer, "ADD TA.xy, TA, %s;\n", reg_coord);
    }

    shader_hw_sample(ins, reg_dest_code, dst_reg, "TA", 0, NULL, NULL);

    if (ins->handler_idx == WINED3DSIH_TEXBEML)
    {
        /* No src swizzles are allowed, so this is ok */
        shader_addline(buffer, "MAD TA, %s.z, luminance%d.x, luminance%d.y;\n",
                       src_reg, reg_dest_code, reg_dest_code);
        shader_addline(buffer, "MUL %s, %s, TA;\n", dst_reg, dst_reg);
    }
}