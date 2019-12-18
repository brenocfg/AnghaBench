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
struct wined3d_shader_version {int major; } ;
struct wined3d_shader_instruction {TYPE_4__* ctx; } ;
struct TYPE_8__ {int /*<<< orphan*/  buffer; TYPE_3__* state; TYPE_2__* shader; } ;
struct TYPE_7__ {int /*<<< orphan*/  in_subroutine; } ;
struct TYPE_5__ {struct wined3d_shader_version shader_version; } ;
struct TYPE_6__ {TYPE_1__ reg_maps; } ;

/* Variables and functions */
 int /*<<< orphan*/  shader_addline (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shader_glsl_generate_shader_epilogue (TYPE_4__*) ; 

__attribute__((used)) static void shader_glsl_ret(const struct wined3d_shader_instruction *ins)
{
    const struct wined3d_shader_version *version = &ins->ctx->shader->reg_maps.shader_version;

    if (version->major >= 4 && !ins->ctx->state->in_subroutine)
    {
        shader_glsl_generate_shader_epilogue(ins->ctx);
        shader_addline(ins->ctx->buffer, "return;\n");
    }
}