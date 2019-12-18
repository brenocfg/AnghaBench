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
struct wined3d_shader_instruction {TYPE_1__* ctx; int /*<<< orphan*/ * src; int /*<<< orphan*/ * dst; } ;
struct glsl_src_param {int /*<<< orphan*/  param_str; } ;
struct TYPE_2__ {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  WINED3DSP_WRITEMASK_1 ; 
 int /*<<< orphan*/  WINED3DSP_WRITEMASK_2 ; 
 int /*<<< orphan*/  WINED3DSP_WRITEMASK_3 ; 
 int /*<<< orphan*/  shader_addline (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct glsl_src_param*) ; 
 int /*<<< orphan*/  shader_glsl_append_dst (int /*<<< orphan*/ ,struct wined3d_shader_instruction const*) ; 
 int /*<<< orphan*/  shader_glsl_get_write_mask (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void shader_glsl_dst(const struct wined3d_shader_instruction *ins)
{
    struct glsl_src_param src0y_param;
    struct glsl_src_param src0z_param;
    struct glsl_src_param src1y_param;
    struct glsl_src_param src1w_param;
    char dst_mask[6];

    shader_glsl_append_dst(ins->ctx->buffer, ins);
    shader_glsl_get_write_mask(&ins->dst[0], dst_mask);

    shader_glsl_add_src_param(ins, &ins->src[0], WINED3DSP_WRITEMASK_1, &src0y_param);
    shader_glsl_add_src_param(ins, &ins->src[0], WINED3DSP_WRITEMASK_2, &src0z_param);
    shader_glsl_add_src_param(ins, &ins->src[1], WINED3DSP_WRITEMASK_1, &src1y_param);
    shader_glsl_add_src_param(ins, &ins->src[1], WINED3DSP_WRITEMASK_3, &src1w_param);

    shader_addline(ins->ctx->buffer, "vec4(1.0, %s * %s, %s, %s))%s;\n",
            src0y_param.param_str, src1y_param.param_str, src0z_param.param_str, src1w_param.param_str, dst_mask);
}