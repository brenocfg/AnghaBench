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
struct wined3d_shader_instruction {scalar_t__ flags; TYPE_1__* ctx; int /*<<< orphan*/ * src; } ;
struct glsl_src_param {int /*<<< orphan*/  param_str; } ;
struct TYPE_2__ {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  WINED3DSP_WRITEMASK_0 ; 
 scalar_t__ WINED3D_SHADER_CONDITIONAL_OP_NZ ; 
 int /*<<< orphan*/  shader_addline (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct glsl_src_param*) ; 

__attribute__((used)) static void shader_glsl_generate_conditional_op(const struct wined3d_shader_instruction *ins,
        const char *op)
{
    struct glsl_src_param src_param;
    const char *condition;

    condition = ins->flags == WINED3D_SHADER_CONDITIONAL_OP_NZ ? "bool" : "!bool";
    shader_glsl_add_src_param(ins, &ins->src[0], WINED3DSP_WRITEMASK_0, &src_param);
    shader_addline(ins->ctx->buffer, "if (%s(%s)) %s\n", condition, src_param.param_str, op);
}