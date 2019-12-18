#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_instruction {int handler_idx; unsigned int src_count; struct wined3d_shader_dst_param* dst; TYPE_6__* src; TYPE_1__* ctx; } ;
struct TYPE_11__ {scalar_t__ type; scalar_t__ data_type; TYPE_2__* idx; } ;
struct wined3d_shader_dst_param {unsigned int write_mask; TYPE_5__ reg; } ;
struct glsl_src_param {char* param_str; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_3__* idx; } ;
struct TYPE_12__ {TYPE_4__ reg; } ;
struct TYPE_9__ {scalar_t__ offset; } ;
struct TYPE_8__ {scalar_t__ offset; } ;
struct TYPE_7__ {struct wined3d_string_buffer* buffer; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
#define  WINED3DSIH_BFI 130 
#define  WINED3DSIH_IBFE 129 
#define  WINED3DSIH_UBFE 128 
 unsigned int WINED3DSP_WRITEMASK_0 ; 
 scalar_t__ WINED3D_DATA_FLOAT ; 
 scalar_t__ WINED3D_DATA_INT ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char const*,...) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,TYPE_6__*,int /*<<< orphan*/ ,struct glsl_src_param*) ; 
 int /*<<< orphan*/  shader_glsl_append_dst_ext (struct wined3d_string_buffer*,struct wined3d_shader_instruction const*,struct wined3d_shader_dst_param*,scalar_t__) ; 
 int /*<<< orphan*/  shader_glsl_get_write_mask (struct wined3d_shader_dst_param*,char*) ; 

__attribute__((used)) static void shader_glsl_bitwise_op(const struct wined3d_shader_instruction *ins)
{
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    struct wined3d_shader_dst_param dst;
    struct glsl_src_param src[4];
    const char *instruction;
    BOOL tmp_dst = FALSE;
    char mask_char[6];
    unsigned int i, j;
    DWORD write_mask;

    switch (ins->handler_idx)
    {
        case WINED3DSIH_BFI:  instruction = "bitfieldInsert";  break;
        case WINED3DSIH_IBFE: instruction = "bitfieldExtract"; break;
        case WINED3DSIH_UBFE: instruction = "bitfieldExtract"; break;
        default:
            ERR("Unhandled opcode %#x.\n", ins->handler_idx);
            return;
    }

    for (i = 0; i < ins->src_count; ++i)
    {
        if (ins->dst[0].reg.idx[0].offset == ins->src[i].reg.idx[0].offset
                && ins->dst[0].reg.type == ins->src[i].reg.type)
            tmp_dst = TRUE;
    }

    dst = ins->dst[0];
    for (i = 0; i < 4; ++i)
    {
        dst.write_mask = ins->dst[0].write_mask & (WINED3DSP_WRITEMASK_0 << i);
        if (tmp_dst && (write_mask = shader_glsl_get_write_mask(&dst, mask_char)))
            shader_addline(buffer, "tmp0%s = %sBitsToFloat(", mask_char,
                    dst.reg.data_type == WINED3D_DATA_INT ? "int" : "uint");
        else if (!(write_mask = shader_glsl_append_dst_ext(buffer, ins, &dst, dst.reg.data_type)))
            continue;

        for (j = 0; j < ins->src_count; ++j)
            shader_glsl_add_src_param(ins, &ins->src[j], write_mask, &src[j]);
        shader_addline(buffer, "%s(", instruction);
        for (j = 0; j < ins->src_count - 2; ++j)
            shader_addline(buffer, "%s, ", src[ins->src_count - j - 1].param_str);
        shader_addline(buffer, "%s & 0x1f, %s & 0x1f));\n", src[1].param_str, src[0].param_str);
    }

    if (tmp_dst)
    {
        shader_glsl_append_dst_ext(buffer, ins, &ins->dst[0], WINED3D_DATA_FLOAT);
        shader_glsl_get_write_mask(&ins->dst[0], mask_char);
        shader_addline(buffer, "tmp0%s);\n", mask_char);
    }
}