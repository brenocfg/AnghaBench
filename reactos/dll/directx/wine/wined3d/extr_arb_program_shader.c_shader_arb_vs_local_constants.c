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
struct wined3d_state {TYPE_1__* vs_consts_i; } ;
struct wined3d_gl_info {int dummy; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
struct arb_vs_compiled_shader {scalar_t__ pos_fixup; scalar_t__* int_consts; int /*<<< orphan*/  num_int_consts; } ;
struct TYPE_2__ {scalar_t__ z; scalar_t__ y; scalar_t__ x; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_VERTEX_PROGRAM_ARB ; 
 scalar_t__ WINED3D_CONST_NUM_UNUSED ; 
 unsigned char WINED3D_MAX_CONSTS_I ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glProgramLocalParameter4fvARB (int /*<<< orphan*/ ,scalar_t__,float*) ; 
 int /*<<< orphan*/  shader_get_position_fixup (struct wined3d_context const*,struct wined3d_state const*,float*) ; 

__attribute__((used)) static void shader_arb_vs_local_constants(const struct arb_vs_compiled_shader *gl_shader,
        const struct wined3d_context *context, const struct wined3d_state *state)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    float position_fixup[4];
    unsigned char i;

    /* Upload the position fixup */
    shader_get_position_fixup(context, state, position_fixup);
    GL_EXTCALL(glProgramLocalParameter4fvARB(GL_VERTEX_PROGRAM_ARB, gl_shader->pos_fixup, position_fixup));

    if (!gl_shader->num_int_consts) return;

    for (i = 0; i < WINED3D_MAX_CONSTS_I; ++i)
    {
        if(gl_shader->int_consts[i] != WINED3D_CONST_NUM_UNUSED)
        {
            float val[4];
            val[0] = (float)state->vs_consts_i[i].x;
            val[1] = (float)state->vs_consts_i[i].y;
            val[2] = (float)state->vs_consts_i[i].z;
            val[3] = -1.0f;

            GL_EXTCALL(glProgramLocalParameter4fvARB(GL_VERTEX_PROGRAM_ARB, gl_shader->int_consts[i], val));
        }
    }
    checkGLcall("Load vs int consts");
}