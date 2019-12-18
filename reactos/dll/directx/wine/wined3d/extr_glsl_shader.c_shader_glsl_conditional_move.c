#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wined3d_shader_instruction {int handler_idx; TYPE_2__* ctx; struct wined3d_shader_dst_param* dst; TYPE_4__* src; } ;
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/  data_type; TYPE_1__* idx; } ;
struct wined3d_shader_dst_param {unsigned int write_mask; TYPE_3__ reg; } ;
struct glsl_src_param {int /*<<< orphan*/  param_str; } ;
struct TYPE_8__ {int /*<<< orphan*/  swizzle; TYPE_3__ reg; } ;
struct TYPE_6__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_5__ {scalar_t__ offset; } ;
typedef  unsigned int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 scalar_t__ TRUE ; 
#define  WINED3DSIH_CMP 130 
#define  WINED3DSIH_CND 129 
#define  WINED3DSIH_MOVC 128 
 unsigned int WINED3DSP_WRITEMASK_0 ; 
 int /*<<< orphan*/  shader_addline (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,TYPE_4__*,unsigned int,struct glsl_src_param*) ; 
 unsigned int shader_glsl_append_dst (int /*<<< orphan*/ ,struct wined3d_shader_instruction const*) ; 
 unsigned int shader_glsl_append_dst_ext (int /*<<< orphan*/ ,struct wined3d_shader_instruction const*,struct wined3d_shader_dst_param*,int /*<<< orphan*/ ) ; 
 unsigned int shader_glsl_get_write_mask (struct wined3d_shader_dst_param*,char*) ; 
 unsigned int shader_glsl_swizzle_get_component (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ shader_is_scalar (TYPE_3__*) ; 

__attribute__((used)) static void shader_glsl_conditional_move(const struct wined3d_shader_instruction *ins)
{
    const char *condition_prefix, *condition_suffix;
    struct wined3d_shader_dst_param dst;
    struct glsl_src_param src0_param;
    struct glsl_src_param src1_param;
    struct glsl_src_param src2_param;
    BOOL temp_destination = FALSE;
    DWORD cmp_channel = 0;
    unsigned int i, j;
    char mask_char[6];
    DWORD write_mask;

    switch (ins->handler_idx)
    {
        case WINED3DSIH_CMP:
            condition_prefix = "";
            condition_suffix = " >= 0.0";
            break;

        case WINED3DSIH_CND:
            condition_prefix = "";
            condition_suffix = " > 0.5";
            break;

        case WINED3DSIH_MOVC:
            condition_prefix = "bool(";
            condition_suffix = ")";
            break;

        default:
            FIXME("Unhandled instruction %#x.\n", ins->handler_idx);
            condition_prefix = "<unhandled prefix>";
            condition_suffix = "<unhandled suffix>";
            break;
    }

    if (shader_is_scalar(&ins->dst[0].reg) || shader_is_scalar(&ins->src[0].reg))
    {
        write_mask = shader_glsl_append_dst(ins->ctx->buffer, ins);
        shader_glsl_add_src_param(ins, &ins->src[0], write_mask, &src0_param);
        shader_glsl_add_src_param(ins, &ins->src[1], write_mask, &src1_param);
        shader_glsl_add_src_param(ins, &ins->src[2], write_mask, &src2_param);

        shader_addline(ins->ctx->buffer, "%s%s%s ? %s : %s);\n",
                condition_prefix, src0_param.param_str, condition_suffix,
                src1_param.param_str, src2_param.param_str);
        return;
    }

    dst = ins->dst[0];

    /* Splitting the instruction up in multiple lines imposes a problem:
     * The first lines may overwrite source parameters of the following lines.
     * Deal with that by using a temporary destination register if needed. */
    if ((ins->src[0].reg.idx[0].offset == dst.reg.idx[0].offset
                && ins->src[0].reg.type == dst.reg.type)
            || (ins->src[1].reg.idx[0].offset == dst.reg.idx[0].offset
                && ins->src[1].reg.type == dst.reg.type)
            || (ins->src[2].reg.idx[0].offset == dst.reg.idx[0].offset
                && ins->src[2].reg.type == dst.reg.type))
        temp_destination = TRUE;

    /* Cycle through all source0 channels. */
    for (i = 0; i < 4; ++i)
    {
        write_mask = 0;
        /* Find the destination channels which use the current source0 channel. */
        for (j = 0; j < 4; ++j)
        {
            if (shader_glsl_swizzle_get_component(ins->src[0].swizzle, j) == i)
            {
                write_mask |= WINED3DSP_WRITEMASK_0 << j;
                cmp_channel = WINED3DSP_WRITEMASK_0 << j;
            }
        }
        dst.write_mask = ins->dst[0].write_mask & write_mask;

        if (temp_destination)
        {
            if (!(write_mask = shader_glsl_get_write_mask(&dst, mask_char)))
                continue;
            shader_addline(ins->ctx->buffer, "tmp0%s = (", mask_char);
        }
        else if (!(write_mask = shader_glsl_append_dst_ext(ins->ctx->buffer, ins, &dst, dst.reg.data_type)))
            continue;

        shader_glsl_add_src_param(ins, &ins->src[0], cmp_channel, &src0_param);
        shader_glsl_add_src_param(ins, &ins->src[1], write_mask, &src1_param);
        shader_glsl_add_src_param(ins, &ins->src[2], write_mask, &src2_param);

        shader_addline(ins->ctx->buffer, "%s%s%s ? %s : %s);\n",
                condition_prefix, src0_param.param_str, condition_suffix,
                src1_param.param_str, src2_param.param_str);
    }

    if (temp_destination)
    {
        shader_glsl_get_write_mask(&ins->dst[0], mask_char);
        shader_glsl_append_dst(ins->ctx->buffer, ins);
        shader_addline(ins->ctx->buffer, "tmp0%s);\n", mask_char);
    }
}