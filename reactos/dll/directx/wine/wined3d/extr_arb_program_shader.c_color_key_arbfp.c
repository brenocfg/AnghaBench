#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  src_blt_color_key; } ;
struct TYPE_3__ {int /*<<< orphan*/  format; } ;
struct wined3d_texture {TYPE_2__ async; TYPE_1__ resource; } ;
struct wined3d_state {struct wined3d_texture** textures; } ;
struct wined3d_gl_info {int dummy; } ;
struct wined3d_device {struct shader_arb_priv* shader_priv; int /*<<< orphan*/ * shader_backend; } ;
struct wined3d_context {struct wined3d_device* device; struct wined3d_gl_info* gl_info; } ;
struct wined3d_color {int /*<<< orphan*/  r; } ;
struct shader_arb_priv {int* pshader_const_dirty; int /*<<< orphan*/  highest_dirty_ps_const; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 size_t ARB_FFP_CONST_COLOR_KEY_HIGH ; 
 size_t ARB_FFP_CONST_COLOR_KEY_LOW ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FRAGMENT_PROGRAM_ARB ; 
 int /*<<< orphan*/  arb_program_shader_backend ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glProgramEnvParameter4fvARB (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ use_ps (struct wined3d_state const*) ; 
 int /*<<< orphan*/  wined3d_format_get_float_color_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct wined3d_color*) ; 

__attribute__((used)) static void color_key_arbfp(struct wined3d_context *context, const struct wined3d_state *state, DWORD state_id)
{
    const struct wined3d_texture *texture = state->textures[0];
    const struct wined3d_gl_info *gl_info = context->gl_info;
    struct wined3d_device *device = context->device;
    struct wined3d_color float_key[2];

    if (!texture)
        return;

    if (device->shader_backend == &arb_program_shader_backend)
    {
        struct shader_arb_priv *priv;

        /* Don't load the parameter if we're using an arbfp pixel shader,
         * otherwise we'll overwrite application provided constants. */
        if (use_ps(state))
            return;

        priv = device->shader_priv;
        priv->pshader_const_dirty[ARB_FFP_CONST_COLOR_KEY_LOW] = 1;
        priv->pshader_const_dirty[ARB_FFP_CONST_COLOR_KEY_HIGH] = 1;
        priv->highest_dirty_ps_const = max(priv->highest_dirty_ps_const, ARB_FFP_CONST_COLOR_KEY_HIGH + 1);
    }

    wined3d_format_get_float_color_key(texture->resource.format, &texture->async.src_blt_color_key, float_key);

    GL_EXTCALL(glProgramEnvParameter4fvARB(GL_FRAGMENT_PROGRAM_ARB, ARB_FFP_CONST_COLOR_KEY_LOW, &float_key[0].r));
    checkGLcall("glProgramEnvParameter4fvARB(GL_FRAGMENT_PROGRAM_ARB, ARB_FFP_CONST_COLOR_KEY_LOW, &float_key[0].r)");
    GL_EXTCALL(glProgramEnvParameter4fvARB(GL_FRAGMENT_PROGRAM_ARB, ARB_FFP_CONST_COLOR_KEY_HIGH, &float_key[1].r));
    checkGLcall("glProgramEnvParameter4fvARB(GL_FRAGMENT_PROGRAM_ARB, ARB_FFP_CONST_COLOR_KEY_HIGH, &float_key[1].r)");
}