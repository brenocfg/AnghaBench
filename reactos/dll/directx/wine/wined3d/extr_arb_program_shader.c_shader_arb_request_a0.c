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
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_instruction {TYPE_1__* ctx; } ;
struct shader_arb_ctx_priv {int /*<<< orphan*/  addr_reg; } ;
struct TYPE_2__ {struct wined3d_string_buffer* buffer; struct shader_arb_ctx_priv* backend_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void shader_arb_request_a0(const struct wined3d_shader_instruction *ins, const char *src)
{
    struct shader_arb_ctx_priv *priv = ins->ctx->backend_data;
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;

    if (!strcmp(priv->addr_reg, src)) return;

    strcpy(priv->addr_reg, src);
    shader_addline(buffer, "ARL A0.x, %s;\n", src);
}