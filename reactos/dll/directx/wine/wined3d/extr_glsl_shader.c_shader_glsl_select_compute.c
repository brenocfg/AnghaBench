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
struct wined3d_state {int dummy; } ;
struct wined3d_gl_info {int dummy; } ;
struct wined3d_context {unsigned int shader_update_mask; struct wined3d_gl_info* gl_info; struct glsl_context_data* shader_backend_data; } ;
struct shader_glsl_priv {int dummy; } ;
struct glsl_context_data {TYPE_1__* glsl_program; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 unsigned int WINED3D_SHADER_TYPE_DOMAIN ; 
 unsigned int WINED3D_SHADER_TYPE_GEOMETRY ; 
 unsigned int WINED3D_SHADER_TYPE_HULL ; 
 unsigned int WINED3D_SHADER_TYPE_PIXEL ; 
 unsigned int WINED3D_SHADER_TYPE_VERTEX ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_glsl_compute_shader_program (struct wined3d_context*,struct wined3d_state const*,struct shader_glsl_priv*,struct glsl_context_data*) ; 

__attribute__((used)) static void shader_glsl_select_compute(void *shader_priv, struct wined3d_context *context,
        const struct wined3d_state *state)
{
    struct glsl_context_data *ctx_data = context->shader_backend_data;
    const struct wined3d_gl_info *gl_info = context->gl_info;
    struct shader_glsl_priv *priv = shader_priv;
    GLuint program_id, prev_id;

    prev_id = ctx_data->glsl_program ? ctx_data->glsl_program->id : 0;
    set_glsl_compute_shader_program(context, state, priv, ctx_data);
    program_id = ctx_data->glsl_program ? ctx_data->glsl_program->id : 0;

    TRACE("Using GLSL program %u.\n", program_id);

    if (prev_id != program_id)
    {
        GL_EXTCALL(glUseProgram(program_id));
        checkGLcall("glUseProgram");
    }

    context->shader_update_mask |= (1u << WINED3D_SHADER_TYPE_PIXEL)
            | (1u << WINED3D_SHADER_TYPE_VERTEX)
            | (1u << WINED3D_SHADER_TYPE_GEOMETRY)
            | (1u << WINED3D_SHADER_TYPE_HULL)
            | (1u << WINED3D_SHADER_TYPE_DOMAIN);
}