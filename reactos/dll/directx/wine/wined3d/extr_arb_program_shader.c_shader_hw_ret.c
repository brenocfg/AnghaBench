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
struct wined3d_shader_instruction {TYPE_2__* ctx; } ;
struct wined3d_shader {int /*<<< orphan*/  backend_data; } ;
struct shader_arb_ctx_priv {scalar_t__ target_version; int /*<<< orphan*/  cur_vs_args; scalar_t__ in_main_func; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_6__ {TYPE_1__ shader_version; } ;
struct TYPE_5__ {int /*<<< orphan*/  gl_info; TYPE_3__* reg_maps; struct wined3d_shader* shader; struct shader_arb_ctx_priv* backend_data; struct wined3d_string_buffer* buffer; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ARB ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*) ; 
 scalar_t__ shader_is_vshader_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vshader_add_footer (struct shader_arb_ctx_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,struct wined3d_string_buffer*) ; 

__attribute__((used)) static void shader_hw_ret(const struct wined3d_shader_instruction *ins)
{
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    struct shader_arb_ctx_priv *priv = ins->ctx->backend_data;
    const struct wined3d_shader *shader = ins->ctx->shader;
    BOOL vshader = shader_is_vshader_version(ins->ctx->reg_maps->shader_version.type);

    if(priv->target_version == ARB) return;

    if(vshader)
    {
        if (priv->in_main_func) vshader_add_footer(priv, shader->backend_data,
                priv->cur_vs_args, ins->ctx->reg_maps, ins->ctx->gl_info, buffer);
    }

    shader_addline(buffer, "RET;\n");
}