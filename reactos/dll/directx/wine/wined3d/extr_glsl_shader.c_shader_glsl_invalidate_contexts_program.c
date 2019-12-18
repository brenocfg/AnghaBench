#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wined3d_device {unsigned int context_count; struct wined3d_context** contexts; } ;
struct wined3d_context {struct glsl_context_data* shader_backend_data; } ;
struct glsl_shader_prog_link {int dummy; } ;
struct glsl_context_data {struct glsl_shader_prog_link const* glsl_program; } ;

/* Variables and functions */
 int /*<<< orphan*/  shader_glsl_invalidate_current_program (struct wined3d_context*) ; 

__attribute__((used)) static void shader_glsl_invalidate_contexts_program(struct wined3d_device *device,
        const struct glsl_shader_prog_link *program)
{
    const struct glsl_context_data *ctx_data;
    struct wined3d_context *context;
    unsigned int i;

    for (i = 0; i < device->context_count; ++i)
    {
        context = device->contexts[i];
        ctx_data = context->shader_backend_data;

        if (ctx_data->glsl_program == program)
            shader_glsl_invalidate_current_program(context);
    }
}