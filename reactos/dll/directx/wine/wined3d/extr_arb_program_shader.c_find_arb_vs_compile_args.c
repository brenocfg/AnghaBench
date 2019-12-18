#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct wined3d_state {TYPE_7__* vs_consts_i; scalar_t__* vs_consts_b; scalar_t__* render_states; struct wined3d_shader** shader; } ;
struct TYPE_13__ {unsigned int local_bool_consts; int integer_constants; int local_int_consts; } ;
struct wined3d_shader {TYPE_6__ reg_maps; struct arb_pshader_private* backend_data; struct wined3d_device* device; } ;
struct wined3d_gl_info {scalar_t__* supported; } ;
struct wined3d_device {struct wined3d_adapter* adapter; } ;
struct TYPE_9__ {int ffp_blend_stages; } ;
struct wined3d_d3d_info {TYPE_2__ limits; int /*<<< orphan*/  vs_clipping; } ;
struct TYPE_8__ {int /*<<< orphan*/  swizzle_map; } ;
struct wined3d_context {scalar_t__* tex_unit_map; TYPE_1__ stream_info; struct wined3d_d3d_info* d3d_info; struct wined3d_gl_info* gl_info; } ;
struct wined3d_adapter {int /*<<< orphan*/ * fragment_pipe; } ;
struct TYPE_12__ {scalar_t__* samplers; } ;
struct TYPE_10__ {int clip_texcoord; unsigned char clipplane_mask; unsigned int bools; } ;
struct TYPE_11__ {TYPE_3__ boolclip; scalar_t__ boolclip_compare; } ;
struct arb_vs_compile_args {scalar_t__** loop_ctrl; TYPE_5__ vertex; TYPE_4__ clip; int /*<<< orphan*/  ps_signature; int /*<<< orphan*/  super; } ;
struct arb_pshader_private {int clipplane_emulation; int /*<<< orphan*/  input_signature_idx; } ;
typedef  int WORD ;
struct TYPE_14__ {scalar_t__ z; scalar_t__ y; scalar_t__ x; } ;

/* Variables and functions */
 int MAX_FRAGMENT_SAMPLERS ; 
 size_t NV_VERTEX_PROGRAM2_OPTION ; 
 int WINED3D_MAX_CONSTS_B ; 
 int WINED3D_MAX_CONSTS_I ; 
 size_t WINED3D_RS_CLIPPING ; 
 size_t WINED3D_RS_CLIPPLANEENABLE ; 
 size_t WINED3D_SHADER_TYPE_PIXEL ; 
 int /*<<< orphan*/  arbfp_fragment_pipeline ; 
 scalar_t__ ffp_clip_emul (struct wined3d_context const*) ; 
 int /*<<< orphan*/  find_vs_compile_args (struct wined3d_state const*,struct wined3d_shader const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct wined3d_context const*) ; 
 int /*<<< orphan*/  memset (scalar_t__**,int /*<<< orphan*/ ,int) ; 
 scalar_t__ use_ps (struct wined3d_state const*) ; 

__attribute__((used)) static void find_arb_vs_compile_args(const struct wined3d_state *state,
        const struct wined3d_context *context, const struct wined3d_shader *shader,
        struct arb_vs_compile_args *args)
{
    const struct wined3d_device *device = shader->device;
    const struct wined3d_adapter *adapter = device->adapter;
    const struct wined3d_gl_info *gl_info = context->gl_info;
    const struct wined3d_d3d_info *d3d_info = context->d3d_info;
    int i;
    WORD int_skip;

    find_vs_compile_args(state, shader, context->stream_info.swizzle_map, &args->super, context);

    args->clip.boolclip_compare = 0;
    if (use_ps(state))
    {
        const struct wined3d_shader *ps = state->shader[WINED3D_SHADER_TYPE_PIXEL];
        const struct arb_pshader_private *shader_priv = ps->backend_data;
        args->ps_signature = shader_priv->input_signature_idx;

        args->clip.boolclip.clip_texcoord = shader_priv->clipplane_emulation + 1;
    }
    else
    {
        args->ps_signature = ~0;
        if (!d3d_info->vs_clipping && adapter->fragment_pipe == &arbfp_fragment_pipeline)
            args->clip.boolclip.clip_texcoord = ffp_clip_emul(context) ? d3d_info->limits.ffp_blend_stages : 0;
        /* Otherwise: Setting boolclip_compare set clip_texcoord to 0 */
    }

    if (args->clip.boolclip.clip_texcoord)
    {
        if (state->render_states[WINED3D_RS_CLIPPING])
            args->clip.boolclip.clipplane_mask = (unsigned char)state->render_states[WINED3D_RS_CLIPPLANEENABLE];
        /* clipplane_mask was set to 0 by setting boolclip_compare to 0 */
    }

    /* This forces all local boolean constants to 1 to make them stateblock independent */
    args->clip.boolclip.bools = shader->reg_maps.local_bool_consts;
    /* TODO: Figure out if it would be better to store bool constants as bitmasks in the stateblock */
    for (i = 0; i < WINED3D_MAX_CONSTS_B; ++i)
    {
        if (state->vs_consts_b[i])
            args->clip.boolclip.bools |= (1u << i);
    }

    args->vertex.samplers[0] = context->tex_unit_map[MAX_FRAGMENT_SAMPLERS + 0];
    args->vertex.samplers[1] = context->tex_unit_map[MAX_FRAGMENT_SAMPLERS + 1];
    args->vertex.samplers[2] = context->tex_unit_map[MAX_FRAGMENT_SAMPLERS + 2];
    args->vertex.samplers[3] = 0;

    /* Skip if unused or local */
    int_skip = ~shader->reg_maps.integer_constants | shader->reg_maps.local_int_consts;
    /* This is about flow control, not clipping. */
    if (int_skip == 0xffff || gl_info->supported[NV_VERTEX_PROGRAM2_OPTION])
    {
        memset(args->loop_ctrl, 0, sizeof(args->loop_ctrl));
        return;
    }

    for (i = 0; i < WINED3D_MAX_CONSTS_I; ++i)
    {
        if (int_skip & (1u << i))
        {
            args->loop_ctrl[i][0] = 0;
            args->loop_ctrl[i][1] = 0;
            args->loop_ctrl[i][2] = 0;
        }
        else
        {
            args->loop_ctrl[i][0] = state->vs_consts_i[i].x;
            args->loop_ctrl[i][1] = state->vs_consts_i[i].y;
            args->loop_ctrl[i][2] = state->vs_consts_i[i].z;
        }
    }
}