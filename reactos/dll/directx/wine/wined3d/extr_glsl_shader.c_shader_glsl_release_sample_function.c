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
struct wined3d_shader_context {struct shader_glsl_ctx_priv* backend_data; } ;
struct shader_glsl_ctx_priv {int /*<<< orphan*/  string_buffers; } ;
struct glsl_sample_function {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  string_buffer_release (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shader_glsl_release_sample_function(const struct wined3d_shader_context *ctx,
        struct glsl_sample_function *sample_function)
{
    const struct shader_glsl_ctx_priv *priv = ctx->backend_data;

    string_buffer_release(priv->string_buffers, sample_function->name);
}