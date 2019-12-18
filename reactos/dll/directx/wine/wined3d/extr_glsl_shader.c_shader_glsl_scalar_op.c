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
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_instruction {int handler_idx; int /*<<< orphan*/ * src; TYPE_3__* ctx; } ;
struct glsl_src_param {int /*<<< orphan*/  param_str; } ;
struct TYPE_6__ {struct wined3d_string_buffer* buffer; TYPE_2__* reg_maps; } ;
struct TYPE_4__ {int major; int /*<<< orphan*/  minor; } ;
struct TYPE_5__ {TYPE_1__ shader_version; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  WINED3DSIH_EXP 133 
#define  WINED3DSIH_EXPP 132 
#define  WINED3DSIH_LOG 131 
#define  WINED3DSIH_LOGP 130 
#define  WINED3DSIH_RCP 129 
#define  WINED3DSIH_RSQ 128 
 int /*<<< orphan*/  WINED3DSP_WRITEMASK_3 ; 
 int /*<<< orphan*/  WINED3D_SHADER_VERSION (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct glsl_src_param*) ; 
 int /*<<< orphan*/  shader_glsl_append_dst (struct wined3d_string_buffer*,struct wined3d_shader_instruction const*) ; 
 unsigned int shader_glsl_get_write_mask_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shader_glsl_scalar_op(const struct wined3d_shader_instruction *ins)
{
    DWORD shader_version = WINED3D_SHADER_VERSION(ins->ctx->reg_maps->shader_version.major,
            ins->ctx->reg_maps->shader_version.minor);
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    struct glsl_src_param src0_param;
    const char *prefix, *suffix;
    unsigned int dst_size;
    DWORD dst_write_mask;

    dst_write_mask = shader_glsl_append_dst(buffer, ins);
    dst_size = shader_glsl_get_write_mask_size(dst_write_mask);

    if (shader_version < WINED3D_SHADER_VERSION(4, 0))
        dst_write_mask = WINED3DSP_WRITEMASK_3;

    shader_glsl_add_src_param(ins, &ins->src[0], dst_write_mask, &src0_param);

    switch (ins->handler_idx)
    {
        case WINED3DSIH_EXP:
        case WINED3DSIH_EXPP:
            prefix = "exp2(";
            suffix = ")";
            break;

        case WINED3DSIH_LOG:
        case WINED3DSIH_LOGP:
            prefix = "log2(abs(";
            suffix = "))";
            break;

        case WINED3DSIH_RCP:
            prefix = "1.0 / ";
            suffix = "";
            break;

        case WINED3DSIH_RSQ:
            prefix = "inversesqrt(abs(";
            suffix = "))";
            break;

        default:
            prefix = "";
            suffix = "";
            FIXME("Unhandled instruction %#x.\n", ins->handler_idx);
            break;
    }

    if (dst_size > 1 && shader_version < WINED3D_SHADER_VERSION(4, 0))
        shader_addline(buffer, "vec%u(%s%s%s));\n", dst_size, prefix, src0_param.param_str, suffix);
    else
        shader_addline(buffer, "%s%s%s);\n", prefix, src0_param.param_str, suffix);
}