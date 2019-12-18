#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_src_param {int /*<<< orphan*/  swizzle; } ;
struct TYPE_9__ {int major; int /*<<< orphan*/  type; } ;
struct wined3d_shader_reg_maps {TYPE_2__ shader_version; } ;
struct wined3d_shader_instruction {scalar_t__ handler_idx; TYPE_7__* dst; struct wined3d_shader_src_param* src; TYPE_1__* ctx; } ;
struct TYPE_12__ {scalar_t__ color0_mov; } ;
struct TYPE_13__ {TYPE_5__ ps; } ;
struct wined3d_shader {TYPE_6__ u; struct arb_vshader_private* backend_data; } ;
struct shader_arb_ctx_priv {scalar_t__ target_version; char* addr_reg; scalar_t__ ps_post_process; } ;
struct arb_vshader_private {scalar_t__ rel_offset; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_3__* idx; } ;
struct TYPE_14__ {TYPE_4__ reg; } ;
struct TYPE_10__ {int /*<<< orphan*/  offset; } ;
struct TYPE_8__ {struct shader_arb_ctx_priv* backend_data; struct wined3d_string_buffer* buffer; struct wined3d_shader_reg_maps* reg_maps; struct wined3d_shader* shader; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ARB ; 
 int /*<<< orphan*/  ARB_ONE ; 
 int /*<<< orphan*/  ARB_TWO ; 
 int /*<<< orphan*/  ARB_VS_REL_OFFSET ; 
 int /*<<< orphan*/  ARB_ZERO ; 
 scalar_t__ NV2 ; 
 scalar_t__ WINED3DSIH_MOVA ; 
 scalar_t__ WINED3DSPR_ADDR ; 
 scalar_t__ WINED3DSPR_COLOROUT ; 
 int /*<<< orphan*/  WINED3D_SHADER_TYPE_VERTEX ; 
 char* arb_get_helper_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_arb_get_src_param (struct wined3d_shader_instruction const*,struct wined3d_shader_src_param*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shader_arb_get_write_mask (struct wined3d_shader_instruction const*,TYPE_7__*,char*) ; 
 int /*<<< orphan*/  shader_arb_select_component (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_hw_map2gl (struct wined3d_shader_instruction const*) ; 
 scalar_t__ shader_is_pshader_version (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shader_hw_mov(const struct wined3d_shader_instruction *ins)
{
    const struct wined3d_shader *shader = ins->ctx->shader;
    const struct wined3d_shader_reg_maps *reg_maps = ins->ctx->reg_maps;
    BOOL pshader = shader_is_pshader_version(reg_maps->shader_version.type);
    struct shader_arb_ctx_priv *ctx = ins->ctx->backend_data;
    const char *zero = arb_get_helper_value(reg_maps->shader_version.type, ARB_ZERO);
    const char *one = arb_get_helper_value(reg_maps->shader_version.type, ARB_ONE);
    const char *two = arb_get_helper_value(reg_maps->shader_version.type, ARB_TWO);

    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    char src0_param[256];

    if (ins->handler_idx == WINED3DSIH_MOVA)
    {
        const struct arb_vshader_private *shader_data = shader->backend_data;
        char write_mask[6];
        const char *offset = arb_get_helper_value(WINED3D_SHADER_TYPE_VERTEX, ARB_VS_REL_OFFSET);

        if(ctx->target_version >= NV2) {
            shader_hw_map2gl(ins);
            return;
        }
        shader_arb_get_src_param(ins, &ins->src[0], 0, src0_param);
        shader_arb_get_write_mask(ins, &ins->dst[0], write_mask);

        /* This implements the mova formula used in GLSL. The first two instructions
         * prepare the sign() part. Note that it is fine to have my_sign(0.0) = 1.0
         * in this case:
         * mova A0.x, 0.0
         *
         * A0.x = arl(floor(abs(0.0) + 0.5) * 1.0) = floor(0.5) = 0.0 since arl does a floor
         *
         * The ARL is performed when A0 is used - the requested component is read from A0_SHADOW into
         * A0.x. We can use the overwritten component of A0_shadow as temporary storage for the sign.
         */
        shader_addline(buffer, "SGE A0_SHADOW%s, %s, %s;\n", write_mask, src0_param, zero);
        shader_addline(buffer, "MAD A0_SHADOW%s, A0_SHADOW, %s, -%s;\n", write_mask, two, one);

        shader_addline(buffer, "ABS TA%s, %s;\n", write_mask, src0_param);
        shader_addline(buffer, "ADD TA%s, TA, rel_addr_const.x;\n", write_mask);
        shader_addline(buffer, "FLR TA%s, TA;\n", write_mask);
        if (shader_data->rel_offset)
        {
            shader_addline(buffer, "ADD TA%s, TA, %s;\n", write_mask, offset);
        }
        shader_addline(buffer, "MUL A0_SHADOW%s, TA, A0_SHADOW;\n", write_mask);

        ((struct shader_arb_ctx_priv *)ins->ctx->backend_data)->addr_reg[0] = '\0';
    }
    else if (reg_maps->shader_version.major == 1
          && !shader_is_pshader_version(reg_maps->shader_version.type)
          && ins->dst[0].reg.type == WINED3DSPR_ADDR)
    {
        const struct arb_vshader_private *shader_data = shader->backend_data;
        src0_param[0] = '\0';

        if (shader_data->rel_offset && ctx->target_version == ARB)
        {
            const char *offset = arb_get_helper_value(WINED3D_SHADER_TYPE_VERTEX, ARB_VS_REL_OFFSET);
            shader_arb_get_src_param(ins, &ins->src[0], 0, src0_param);
            shader_addline(buffer, "ADD TA.x, %s, %s;\n", src0_param, offset);
            shader_addline(buffer, "ARL A0.x, TA.x;\n");
        }
        else
        {
            /* Apple's ARB_vertex_program implementation does not accept an ARL source argument
             * with more than one component. Thus replicate the first source argument over all
             * 4 components. For example, .xyzw -> .x (or better: .xxxx), .zwxy -> .z, etc) */
            struct wined3d_shader_src_param tmp_src = ins->src[0];
            tmp_src.swizzle = shader_arb_select_component(tmp_src.swizzle, 0);
            shader_arb_get_src_param(ins, &tmp_src, 0, src0_param);
            shader_addline(buffer, "ARL A0.x, %s;\n", src0_param);
        }
    }
    else if (ins->dst[0].reg.type == WINED3DSPR_COLOROUT && !ins->dst[0].reg.idx[0].offset && pshader)
    {
        if (ctx->ps_post_process && shader->u.ps.color0_mov)
        {
            shader_addline(buffer, "#mov handled in srgb write or fog code\n");
            return;
        }
        shader_hw_map2gl(ins);
    }
    else
    {
        shader_hw_map2gl(ins);
    }
}