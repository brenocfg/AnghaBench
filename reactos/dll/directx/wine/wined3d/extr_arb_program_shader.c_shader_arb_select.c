#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct wined3d_state {struct wined3d_shader** shader; TYPE_2__* fb; } ;
struct wined3d_shader_signature {int dummy; } ;
struct wined3d_shader {scalar_t__ load_local_constsF; struct wined3d_shader_signature input_signature; scalar_t__ backend_data; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* p_glDisable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glEnable ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_17__ {TYPE_7__ gl; } ;
struct wined3d_gl_info {TYPE_8__ gl_ops; scalar_t__* supported; } ;
struct TYPE_15__ {int /*<<< orphan*/  use_map; } ;
struct wined3d_context {int /*<<< orphan*/  constant_update_mask; TYPE_6__ stream_info; struct wined3d_gl_info* gl_info; } ;
struct shader_arb_priv {scalar_t__ last_ps_const_clamped; int* pshader_const_dirty; scalar_t__ last_vs_color_unclamp; TYPE_9__* vertex_pipe; struct wined3d_shader* current_vprogram_id; struct arb_vs_compiled_shader* compiled_vprog; TYPE_5__* fragment_pipe; struct wined3d_shader* current_fprogram_id; int /*<<< orphan*/  use_arbfp_fixed_func; int /*<<< orphan*/  highest_dirty_ps_const; struct arb_ps_compiled_shader* compiled_fprog; } ;
struct arb_vs_compiled_shader {scalar_t__ need_color_unclamp; struct wined3d_shader* prgId; } ;
struct arb_vs_compile_args {unsigned int ps_signature; } ;
struct arb_pshader_private {scalar_t__ clamp_consts; } ;
struct TYPE_12__ {scalar_t__ active; } ;
struct TYPE_13__ {TYPE_3__ super; } ;
struct arb_ps_compiled_shader {TYPE_4__ np2fixup_info; struct wined3d_shader* prgId; } ;
struct arb_ps_compile_args {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_18__ {int /*<<< orphan*/  (* vp_enable ) (struct wined3d_gl_info const*,int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  (* enable_extension ) (struct wined3d_gl_info const*,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {TYPE_1__** render_targets; } ;
struct TYPE_10__ {int /*<<< orphan*/  height; } ;

/* Variables and functions */
 size_t ARB_COLOR_BUFFER_FLOAT ; 
 size_t ARB_FRAGMENT_PROGRAM ; 
 size_t ARB_VERTEX_PROGRAM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GL_CLAMP_VERTEX_COLOR_ARB ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FRAGMENT_PROGRAM_ARB ; 
 int /*<<< orphan*/  GL_VERTEX_PROGRAM_ARB ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_shader*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINED3D_SHADER_CONST_PS_F ; 
 int /*<<< orphan*/  WINED3D_SHADER_CONST_PS_NP2_FIXUP ; 
 int /*<<< orphan*/  WINED3D_SHADER_CONST_VS_F ; 
 size_t WINED3D_SHADER_TYPE_PIXEL ; 
 size_t WINED3D_SHADER_TYPE_VERTEX ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  find_arb_ps_compile_args (struct wined3d_state const*,struct wined3d_context*,struct wined3d_shader*,struct arb_ps_compile_args*) ; 
 struct arb_ps_compiled_shader* find_arb_pshader (struct wined3d_shader*,struct arb_ps_compile_args*) ; 
 int /*<<< orphan*/  find_arb_vs_compile_args (struct wined3d_state const*,struct wined3d_context*,struct wined3d_shader*,struct arb_vs_compile_args*) ; 
 struct arb_vs_compiled_shader* find_arb_vshader (struct wined3d_shader*,struct wined3d_gl_info*,int /*<<< orphan*/ ,struct arb_vs_compile_args*,struct wined3d_shader_signature const*) ; 
 int /*<<< orphan*/  glBindProgramARB (int /*<<< orphan*/ ,struct wined3d_shader*) ; 
 int /*<<< orphan*/  glClampColorARB (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  shader_arb_load_constants_internal (void*,struct wined3d_context*,struct wined3d_state const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_arb_ps_local_constants (struct arb_ps_compiled_shader*,struct wined3d_context*,struct wined3d_state const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_arb_vs_local_constants (struct arb_vs_compiled_shader*,struct wined3d_context*,struct wined3d_state const*) ; 
 int /*<<< orphan*/  stub1 (struct wined3d_gl_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct wined3d_gl_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct wined3d_gl_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (struct wined3d_gl_info const*,int /*<<< orphan*/ ) ; 
 scalar_t__ use_ps (struct wined3d_state const*) ; 
 scalar_t__ use_vs (struct wined3d_state const*) ; 

__attribute__((used)) static void shader_arb_select(void *shader_priv, struct wined3d_context *context,
        const struct wined3d_state *state)
{
    struct shader_arb_priv *priv = shader_priv;
    const struct wined3d_gl_info *gl_info = context->gl_info;
    int i;

    /* Deal with pixel shaders first so the vertex shader arg function has the input signature ready */
    if (use_ps(state))
    {
        struct wined3d_shader *ps = state->shader[WINED3D_SHADER_TYPE_PIXEL];
        struct arb_ps_compile_args compile_args;
        struct arb_ps_compiled_shader *compiled;

        TRACE("Using pixel shader %p.\n", ps);
        find_arb_ps_compile_args(state, context, ps, &compile_args);
        compiled = find_arb_pshader(ps, &compile_args);
        priv->current_fprogram_id = compiled->prgId;
        priv->compiled_fprog = compiled;

        /* Bind the fragment program */
        GL_EXTCALL(glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, priv->current_fprogram_id));
        checkGLcall("glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, priv->current_fprogram_id);");

        if (!priv->use_arbfp_fixed_func)
            priv->fragment_pipe->enable_extension(gl_info, FALSE);

        /* Enable OpenGL fragment programs. */
        gl_info->gl_ops.gl.p_glEnable(GL_FRAGMENT_PROGRAM_ARB);
        checkGLcall("glEnable(GL_FRAGMENT_PROGRAM_ARB);");

        TRACE("Bound fragment program %u and enabled GL_FRAGMENT_PROGRAM_ARB\n", priv->current_fprogram_id);

        /* Pixel Shader 1.x constants are clamped to [-1;1], Pixel Shader 2.0 constants are not. If switching between
         * a 1.x and newer shader, reload the first 8 constants
         */
        if (priv->last_ps_const_clamped != ((struct arb_pshader_private *)ps->backend_data)->clamp_consts)
        {
            priv->last_ps_const_clamped = ((struct arb_pshader_private *)ps->backend_data)->clamp_consts;
            priv->highest_dirty_ps_const = max(priv->highest_dirty_ps_const, 8);
            for(i = 0; i < 8; i++)
            {
                priv->pshader_const_dirty[i] = 1;
            }
            /* Also takes care of loading local constants */
            shader_arb_load_constants_internal(shader_priv, context, state, TRUE, FALSE, TRUE);
        }
        else
        {
            UINT rt_height = state->fb->render_targets[0]->height;
            shader_arb_ps_local_constants(compiled, context, state, rt_height);
        }

        /* Force constant reloading for the NP2 fixup (see comment in shader_glsl_select for more info) */
        if (compiled->np2fixup_info.super.active)
            context->constant_update_mask |= WINED3D_SHADER_CONST_PS_NP2_FIXUP;

        if (ps->load_local_constsF)
            context->constant_update_mask |= WINED3D_SHADER_CONST_PS_F;
    }
    else
    {
        if (gl_info->supported[ARB_FRAGMENT_PROGRAM] && !priv->use_arbfp_fixed_func)
        {
            /* Disable only if we're not using arbfp fixed function fragment
             * processing. If this is used, keep GL_FRAGMENT_PROGRAM_ARB
             * enabled, and the fixed function pipeline will bind the fixed
             * function replacement shader. */
            gl_info->gl_ops.gl.p_glDisable(GL_FRAGMENT_PROGRAM_ARB);
            checkGLcall("glDisable(GL_FRAGMENT_PROGRAM_ARB)");
            priv->current_fprogram_id = 0;
        }
        priv->fragment_pipe->enable_extension(gl_info, TRUE);
    }

    if (use_vs(state))
    {
        struct wined3d_shader *vs = state->shader[WINED3D_SHADER_TYPE_VERTEX];
        struct arb_vs_compile_args compile_args;
        struct arb_vs_compiled_shader *compiled;
        const struct wined3d_shader_signature *ps_input_sig;

        TRACE("Using vertex shader %p\n", vs);
        find_arb_vs_compile_args(state, context, vs, &compile_args);

        /* Instead of searching for the signature in the signature list, read the one from the
         * current pixel shader. It's maybe not the shader where the signature came from, but it
         * is the same signature and faster to find. */
        if (compile_args.ps_signature == ~0U)
            ps_input_sig = NULL;
        else
            ps_input_sig = &state->shader[WINED3D_SHADER_TYPE_PIXEL]->input_signature;

        compiled = find_arb_vshader(vs, context->gl_info, context->stream_info.use_map,
                &compile_args, ps_input_sig);
        priv->current_vprogram_id = compiled->prgId;
        priv->compiled_vprog = compiled;

        /* Bind the vertex program */
        GL_EXTCALL(glBindProgramARB(GL_VERTEX_PROGRAM_ARB, priv->current_vprogram_id));
        checkGLcall("glBindProgramARB(GL_VERTEX_PROGRAM_ARB, priv->current_vprogram_id);");

        priv->vertex_pipe->vp_enable(gl_info, FALSE);

        /* Enable OpenGL vertex programs */
        gl_info->gl_ops.gl.p_glEnable(GL_VERTEX_PROGRAM_ARB);
        checkGLcall("glEnable(GL_VERTEX_PROGRAM_ARB);");
        TRACE("Bound vertex program %u and enabled GL_VERTEX_PROGRAM_ARB\n", priv->current_vprogram_id);
        shader_arb_vs_local_constants(compiled, context, state);

        if(priv->last_vs_color_unclamp != compiled->need_color_unclamp) {
            priv->last_vs_color_unclamp = compiled->need_color_unclamp;

            if (gl_info->supported[ARB_COLOR_BUFFER_FLOAT])
            {
                GL_EXTCALL(glClampColorARB(GL_CLAMP_VERTEX_COLOR_ARB, !compiled->need_color_unclamp));
                checkGLcall("glClampColorARB");
            } else {
                FIXME("vertex color clamp needs to be changed, but extension not supported.\n");
            }
        }

        if (vs->load_local_constsF)
            context->constant_update_mask |= WINED3D_SHADER_CONST_VS_F;
    }
    else
    {
        if (gl_info->supported[ARB_VERTEX_PROGRAM])
        {
            priv->current_vprogram_id = 0;
            gl_info->gl_ops.gl.p_glDisable(GL_VERTEX_PROGRAM_ARB);
            checkGLcall("glDisable(GL_VERTEX_PROGRAM_ARB)");
        }
        priv->vertex_pipe->vp_enable(gl_info, TRUE);
    }
}