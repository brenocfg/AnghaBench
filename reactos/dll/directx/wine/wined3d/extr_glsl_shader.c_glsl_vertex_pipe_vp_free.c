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
struct wined3d_device {TYPE_1__* adapter; struct shader_glsl_priv* vertex_priv; } ;
struct shader_glsl_priv {int /*<<< orphan*/  ffp_vertex_shaders; } ;
struct glsl_ffp_destroy_ctx {int /*<<< orphan*/ * gl_info; struct shader_glsl_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  gl_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  shader_glsl_free_ffp_vertex_shader ; 
 int /*<<< orphan*/  wine_rb_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct glsl_ffp_destroy_ctx*) ; 

__attribute__((used)) static void glsl_vertex_pipe_vp_free(struct wined3d_device *device)
{
    struct shader_glsl_priv *priv = device->vertex_priv;
    struct glsl_ffp_destroy_ctx ctx;

    ctx.priv = priv;
    ctx.gl_info = &device->adapter->gl_info;
    wine_rb_destroy(&priv->ffp_vertex_shaders, shader_glsl_free_ffp_vertex_shader, &ctx);
}