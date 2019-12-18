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
struct wined3d_shader_instruction {TYPE_1__* ctx; int /*<<< orphan*/ * dst; } ;
struct glsl_dst_param {int /*<<< orphan*/  reg_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  shader_addline (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_add_dst_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,struct glsl_dst_param*) ; 

__attribute__((used)) static void shader_glsl_texdepth(const struct wined3d_shader_instruction *ins)
{
    struct glsl_dst_param dst_param;

    shader_glsl_add_dst_param(ins, &ins->dst[0], &dst_param);

    /* Tests show that texdepth never returns anything below 0.0, and that r5.y is clamped to 1.0.
     * Negative input is accepted, -0.25 / -0.5 returns 0.5. GL should clamp gl_FragDepth to [0;1], but
     * this doesn't always work, so clamp the results manually. Whether or not the x value is clamped at 1
     * too is irrelevant, since if x = 0, any y value < 1.0 (and > 1.0 is not allowed) results in a result
     * >= 1.0 or < 0.0
     */
    shader_addline(ins->ctx->buffer, "gl_FragDepth = clamp((%s.x / min(%s.y, 1.0)), 0.0, 1.0);\n",
            dst_param.reg_name, dst_param.reg_name);
}