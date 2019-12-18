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
struct wined3d_shader_instruction {TYPE_3__* ctx; int /*<<< orphan*/ * dst; } ;
struct glsl_dst_param {int /*<<< orphan*/  reg_name; } ;
struct TYPE_6__ {int /*<<< orphan*/  buffer; TYPE_2__* reg_maps; } ;
struct TYPE_4__ {int major; } ;
struct TYPE_5__ {TYPE_1__ shader_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  shader_addline (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_add_dst_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,struct glsl_dst_param*) ; 
 int /*<<< orphan*/  shader_glsl_generate_conditional_op (struct wined3d_shader_instruction const*,char*) ; 

__attribute__((used)) static void shader_glsl_texkill(const struct wined3d_shader_instruction *ins)
{
    if (ins->ctx->reg_maps->shader_version.major >= 4)
    {
        shader_glsl_generate_conditional_op(ins, "discard;");
    }
    else
    {
        struct glsl_dst_param dst_param;

        /* The argument is a destination parameter, and no writemasks are allowed */
        shader_glsl_add_dst_param(ins, &ins->dst[0], &dst_param);

        /* 2.0 shaders compare all 4 components in texkill. */
        if (ins->ctx->reg_maps->shader_version.major >= 2)
            shader_addline(ins->ctx->buffer, "if (any(lessThan(%s.xyzw, vec4(0.0)))) discard;\n", dst_param.reg_name);
        /* 1.x shaders only compare the first 3 components, probably due to
         * the nature of the texkill instruction as a tex* instruction, and
         * phase, which kills all .w components. Even if all 4 components are
         * defined, only the first 3 are used. */
        else
            shader_addline(ins->ctx->buffer, "if (any(lessThan(%s.xyz, vec3(0.0)))) discard;\n", dst_param.reg_name);
    }
}