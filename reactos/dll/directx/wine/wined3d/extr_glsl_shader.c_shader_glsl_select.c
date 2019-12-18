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
struct wined3d_state {int dummy; } ;
struct wined3d_gl_info {scalar_t__* supported; } ;
struct wined3d_context {unsigned int shader_update_mask; int /*<<< orphan*/  constant_update_mask; struct wined3d_gl_info* gl_info; struct glsl_context_data* shader_backend_data; } ;
struct shader_glsl_priv {TYPE_2__* fragment_pipe; TYPE_1__* vertex_pipe; } ;
struct TYPE_6__ {scalar_t__ vertex_color_clamp; } ;
struct glsl_shader_prog_link {int /*<<< orphan*/  constant_update_mask; int /*<<< orphan*/  clip_distance_mask; scalar_t__ shader_controlled_clip_distances; TYPE_3__ vs; int /*<<< orphan*/  id; } ;
struct glsl_context_data {scalar_t__ vertex_color_clamp; struct glsl_shader_prog_link* glsl_program; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* enable_extension ) (struct wined3d_gl_info const*,int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* vp_enable ) (struct wined3d_gl_info const*,int) ;} ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  scalar_t__ GLenum ;

/* Variables and functions */
 size_t ARB_COLOR_BUFFER_FLOAT ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GL_CLAMP_VERTEX_COLOR_ARB ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 scalar_t__ GL_FIXED_ONLY_ARB ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 unsigned int WINED3D_SHADER_TYPE_COMPUTE ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  context_enable_clip_distances (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClampColorARB (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_glsl_shader_program (struct wined3d_context*,struct wined3d_state const*,struct shader_glsl_priv*,struct glsl_context_data*) ; 
 int /*<<< orphan*/  stub1 (struct wined3d_gl_info const*,int) ; 
 int /*<<< orphan*/  stub2 (struct wined3d_gl_info const*,int) ; 
 int /*<<< orphan*/  use_ps (struct wined3d_state const*) ; 
 int /*<<< orphan*/  use_vs (struct wined3d_state const*) ; 

__attribute__((used)) static void shader_glsl_select(void *shader_priv, struct wined3d_context *context,
        const struct wined3d_state *state)
{
    struct glsl_context_data *ctx_data = context->shader_backend_data;
    const struct wined3d_gl_info *gl_info = context->gl_info;
    struct shader_glsl_priv *priv = shader_priv;
    struct glsl_shader_prog_link *glsl_program;
    GLenum current_vertex_color_clamp;
    GLuint program_id, prev_id;

    priv->vertex_pipe->vp_enable(gl_info, !use_vs(state));
    priv->fragment_pipe->enable_extension(gl_info, !use_ps(state));

    prev_id = ctx_data->glsl_program ? ctx_data->glsl_program->id : 0;
    set_glsl_shader_program(context, state, priv, ctx_data);
    glsl_program = ctx_data->glsl_program;

    if (glsl_program)
    {
        program_id = glsl_program->id;
        current_vertex_color_clamp = glsl_program->vs.vertex_color_clamp;
        if (glsl_program->shader_controlled_clip_distances)
            context_enable_clip_distances(context, glsl_program->clip_distance_mask);
    }
    else
    {
        program_id = 0;
        current_vertex_color_clamp = GL_FIXED_ONLY_ARB;
    }

    if (ctx_data->vertex_color_clamp != current_vertex_color_clamp)
    {
        ctx_data->vertex_color_clamp = current_vertex_color_clamp;
        if (gl_info->supported[ARB_COLOR_BUFFER_FLOAT])
        {
            GL_EXTCALL(glClampColorARB(GL_CLAMP_VERTEX_COLOR_ARB, current_vertex_color_clamp));
            checkGLcall("glClampColorARB");
        }
        else
        {
            FIXME("Vertex color clamp needs to be changed, but extension not supported.\n");
        }
    }

    TRACE("Using GLSL program %u.\n", program_id);

    if (prev_id != program_id)
    {
        GL_EXTCALL(glUseProgram(program_id));
        checkGLcall("glUseProgram");

        if (glsl_program)
            context->constant_update_mask |= glsl_program->constant_update_mask;
    }

    context->shader_update_mask |= (1u << WINED3D_SHADER_TYPE_COMPUTE);
}