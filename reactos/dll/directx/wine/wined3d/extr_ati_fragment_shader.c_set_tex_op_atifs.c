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
struct wined3d_state {int /*<<< orphan*/ * textures; } ;
struct wined3d_gl_info {int dummy; } ;
struct wined3d_device {struct atifs_private_data* fragment_priv; } ;
struct TYPE_4__ {unsigned int ffp_blend_stages; } ;
struct wined3d_d3d_info {TYPE_1__ limits; } ;
struct wined3d_context {scalar_t__* tex_unit_map; struct atifs_context_private_data* fragment_pipe_data; struct wined3d_d3d_info* d3d_info; struct wined3d_gl_info* gl_info; struct wined3d_device* device; } ;
struct ffp_frag_settings {TYPE_2__* op; } ;
struct atifs_private_data {int /*<<< orphan*/  fragment_shaders; } ;
struct TYPE_6__ {struct ffp_frag_settings settings; } ;
typedef  struct atifs_ffp_desc {unsigned int num_textures_used; int* constants; int /*<<< orphan*/  shader; TYPE_3__ parent; } const atifs_ffp_desc ;
struct atifs_context_private_data {struct atifs_ffp_desc const* last_shader; } ;
struct TYPE_5__ {scalar_t__ cop; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
#define  ATIFS_CONSTANT_BUMP 130 
#define  ATIFS_CONSTANT_STAGE 129 
#define  ATIFS_CONSTANT_TFACTOR 128 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 unsigned int MAX_TEXTURES ; 
 int /*<<< orphan*/  STATE_RENDER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_TEXTURESTAGE (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,struct atifs_ffp_desc const*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINED3D_RS_TEXTUREFACTOR ; 
 scalar_t__ WINED3D_TOP_DISABLE ; 
 int /*<<< orphan*/  WINED3D_TSS_BUMPENV_MAT00 ; 
 int /*<<< orphan*/  WINED3D_TSS_CONSTANT ; 
 scalar_t__ WINED3D_UNMAPPED_STAGE ; 
 int /*<<< orphan*/  add_ffp_frag_shader (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  atifs_stage_constant (struct wined3d_context*,struct wined3d_state const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atifs_tfactor (struct wined3d_context*,struct wined3d_state const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_active_texture (struct wined3d_context*,struct wined3d_gl_info const*,scalar_t__) ; 
 scalar_t__ find_ffp_frag_shader (int /*<<< orphan*/ *,struct ffp_frag_settings*) ; 
 int /*<<< orphan*/  gen_ati_shader (TYPE_2__*,struct wined3d_gl_info const*,int*) ; 
 int /*<<< orphan*/  gen_ffp_frag_op (struct wined3d_context*,struct wined3d_state const*,struct ffp_frag_settings*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindFragmentShaderATI (int /*<<< orphan*/ ) ; 
 struct atifs_ffp_desc const* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  set_bumpmat (struct wined3d_context*,struct wined3d_state const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  texture_activate_dimensions (int /*<<< orphan*/ ,struct wined3d_gl_info const*) ; 

__attribute__((used)) static void set_tex_op_atifs(struct wined3d_context *context, const struct wined3d_state *state, DWORD state_id)
{
    const struct wined3d_device *device = context->device;
    const struct wined3d_gl_info *gl_info = context->gl_info;
    const struct wined3d_d3d_info *d3d_info = context->d3d_info;
    struct atifs_context_private_data *ctx_priv = context->fragment_pipe_data;
    const struct atifs_ffp_desc *desc, *last_shader = ctx_priv->last_shader;
    struct ffp_frag_settings settings;
    struct atifs_private_data *priv = device->fragment_priv;
    DWORD mapped_stage;
    unsigned int i;

    gen_ffp_frag_op(context, state, &settings, TRUE);
    desc = (const struct atifs_ffp_desc *)find_ffp_frag_shader(&priv->fragment_shaders, &settings);
    if (!desc)
    {
        struct atifs_ffp_desc *new_desc;

        if (!(new_desc = heap_alloc_zero(sizeof(*new_desc))))
        {
            ERR("Out of memory\n");
            return;
        }
        new_desc->num_textures_used = 0;
        for (i = 0; i < d3d_info->limits.ffp_blend_stages; ++i)
        {
            if (settings.op[i].cop == WINED3D_TOP_DISABLE)
                break;
            ++new_desc->num_textures_used;
        }

        new_desc->parent.settings = settings;
        new_desc->shader = gen_ati_shader(settings.op, gl_info, new_desc->constants);
        add_ffp_frag_shader(&priv->fragment_shaders, &new_desc->parent);
        TRACE("Allocated fixed function replacement shader descriptor %p.\n", new_desc);
        desc = new_desc;
    }

    /* GL_ATI_fragment_shader depends on the GL_TEXTURE_xD enable settings. Update the texture stages
     * used by this shader
     */
    for (i = 0; i < desc->num_textures_used; ++i)
    {
        mapped_stage = context->tex_unit_map[i];
        if (mapped_stage != WINED3D_UNMAPPED_STAGE)
        {
            context_active_texture(context, gl_info, mapped_stage);
            texture_activate_dimensions(state->textures[i], gl_info);
        }
    }

    GL_EXTCALL(glBindFragmentShaderATI(desc->shader));
    ctx_priv->last_shader = desc;

    for (i = 0; i < MAX_TEXTURES; i++)
    {
        if (last_shader && last_shader->constants[i] == desc->constants[i])
            continue;

        switch (desc->constants[i])
        {
            case ATIFS_CONSTANT_BUMP:
                set_bumpmat(context, state, STATE_TEXTURESTAGE(i, WINED3D_TSS_BUMPENV_MAT00));
                break;

            case ATIFS_CONSTANT_TFACTOR:
                atifs_tfactor(context, state, STATE_RENDER(WINED3D_RS_TEXTUREFACTOR));
                break;

            case ATIFS_CONSTANT_STAGE:
                atifs_stage_constant(context, state, STATE_TEXTURESTAGE(i, WINED3D_TSS_CONSTANT));
                break;

            default:
                ERR("Unexpected constant type %u.\n", desc->constants[i]);
        }
    }
}