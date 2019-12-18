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
struct wined3d_state {int /*<<< orphan*/ * render_states; } ;
struct wined3d_gl_info {int dummy; } ;
struct wined3d_device {struct shader_arb_priv* shader_priv; int /*<<< orphan*/ * shader_backend; } ;
struct wined3d_context {struct wined3d_device* device; struct wined3d_gl_info* gl_info; } ;
struct wined3d_color {int /*<<< orphan*/  r; } ;
struct shader_arb_priv {int* pshader_const_dirty; int /*<<< orphan*/  highest_dirty_ps_const; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 size_t ARB_FFP_CONST_TFACTOR ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FRAGMENT_PROGRAM_ARB ; 
 size_t WINED3D_RS_TEXTUREFACTOR ; 
 int /*<<< orphan*/  arb_program_shader_backend ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glProgramEnvParameter4fvARB (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ use_ps (struct wined3d_state const*) ; 
 int /*<<< orphan*/  wined3d_color_from_d3dcolor (struct wined3d_color*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void state_texfactor_arbfp(struct wined3d_context *context,
        const struct wined3d_state *state, DWORD state_id)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    struct wined3d_device *device = context->device;
    struct wined3d_color color;

    if (device->shader_backend == &arb_program_shader_backend)
    {
        struct shader_arb_priv *priv;

        /* Don't load the parameter if we're using an arbfp pixel shader,
         * otherwise we'll overwrite application provided constants. */
        if (use_ps(state))
            return;

        priv = device->shader_priv;
        priv->pshader_const_dirty[ARB_FFP_CONST_TFACTOR] = 1;
        priv->highest_dirty_ps_const = max(priv->highest_dirty_ps_const, ARB_FFP_CONST_TFACTOR + 1);
    }

    wined3d_color_from_d3dcolor(&color, state->render_states[WINED3D_RS_TEXTUREFACTOR]);
    GL_EXTCALL(glProgramEnvParameter4fvARB(GL_FRAGMENT_PROGRAM_ARB, ARB_FFP_CONST_TFACTOR, &color.r));
    checkGLcall("glProgramEnvParameter4fvARB(GL_FRAGMENT_PROGRAM_ARB, ARB_FFP_CONST_TFACTOR, &color.r)");
}