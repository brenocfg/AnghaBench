#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_instruction {TYPE_8__* dst; TYPE_5__* ctx; } ;
struct wined3d_shader {struct wined3d_device* device; } ;
struct wined3d_gl_info {int /*<<< orphan*/ * supported; } ;
struct wined3d_device {TYPE_2__* adapter; } ;
struct shader_arb_ctx_priv {TYPE_12__* cur_ps_args; TYPE_10__* cur_np2fixup_info; TYPE_7__* cur_vs_args; } ;
struct color_fixup_masks {scalar_t__ sign; scalar_t__ source; } ;
typedef  enum wined3d_shader_resource_type { ____Placeholder_wined3d_shader_resource_type } wined3d_shader_resource_type ;
typedef  int WORD ;
struct TYPE_24__ {unsigned int active; unsigned char* idx; } ;
struct TYPE_23__ {int modifiers; int /*<<< orphan*/  write_mask; } ;
struct TYPE_21__ {size_t* samplers; } ;
struct TYPE_22__ {TYPE_6__ vertex; } ;
struct TYPE_20__ {TYPE_4__* reg_maps; struct wined3d_shader* shader; struct shader_arb_ctx_priv* backend_data; struct wined3d_string_buffer* buffer; } ;
struct TYPE_18__ {int /*<<< orphan*/  type; } ;
struct TYPE_19__ {TYPE_3__ shader_version; TYPE_1__* resource_info; } ;
struct TYPE_17__ {struct wined3d_gl_info gl_info; } ;
struct TYPE_16__ {int type; } ;
struct TYPE_14__ {unsigned int np2_fixup; int /*<<< orphan*/ * color_fixup; } ;
struct TYPE_15__ {TYPE_11__ super; } ;
struct TYPE_13__ {TYPE_9__ super; } ;
typedef  size_t DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARB_ONE ; 
 size_t ARB_TEXTURE_RECTANGLE ; 
 int /*<<< orphan*/  ARB_TWO ; 
 int /*<<< orphan*/  ERR (char*,int) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 size_t MAX_FRAGMENT_SAMPLERS ; 
 int TEX_BIAS ; 
 int TEX_DERIV ; 
 int TEX_LOD ; 
 int TEX_PROJ ; 
 scalar_t__ TRUE ; 
 int WINED3DSPDM_SATURATE ; 
#define  WINED3D_SHADER_RESOURCE_TEXTURE_1D 131 
#define  WINED3D_SHADER_RESOURCE_TEXTURE_2D 130 
#define  WINED3D_SHADER_RESOURCE_TEXTURE_3D 129 
#define  WINED3D_SHADER_RESOURCE_TEXTURE_CUBE 128 
 int /*<<< orphan*/  WINED3D_SHADER_TYPE_PIXEL ; 
 int /*<<< orphan*/  arb_get_helper_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct color_fixup_masks calc_color_correction (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_color_correction (struct wined3d_string_buffer*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct color_fixup_masks) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 scalar_t__ shader_is_pshader_version (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shader_hw_sample(const struct wined3d_shader_instruction *ins, DWORD sampler_idx,
        const char *dst_str, const char *coord_reg, WORD flags, const char *dsx, const char *dsy)
{
    enum wined3d_shader_resource_type resource_type = ins->ctx->reg_maps->resource_info[sampler_idx].type;
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    const char *tex_type;
    BOOL np2_fixup = FALSE;
    struct shader_arb_ctx_priv *priv = ins->ctx->backend_data;
    const char *mod;
    BOOL pshader = shader_is_pshader_version(ins->ctx->reg_maps->shader_version.type);
    const struct wined3d_shader *shader;
    const struct wined3d_device *device;
    const struct wined3d_gl_info *gl_info;
    const char *tex_dst = dst_str;
    struct color_fixup_masks masks;

    /* D3D vertex shader sampler IDs are vertex samplers(0-3), not global d3d samplers */
    if(!pshader) sampler_idx += MAX_FRAGMENT_SAMPLERS;

    switch (resource_type)
    {
        case WINED3D_SHADER_RESOURCE_TEXTURE_1D:
            tex_type = "1D";
            break;

        case WINED3D_SHADER_RESOURCE_TEXTURE_2D:
            shader = ins->ctx->shader;
            device = shader->device;
            gl_info = &device->adapter->gl_info;

            if (pshader && priv->cur_ps_args->super.np2_fixup & (1u << sampler_idx)
                    && gl_info->supported[ARB_TEXTURE_RECTANGLE])
                tex_type = "RECT";
            else
                tex_type = "2D";
            if (shader_is_pshader_version(ins->ctx->reg_maps->shader_version.type))
            {
                if (priv->cur_np2fixup_info->super.active & (1u << sampler_idx))
                {
                    if (flags) FIXME("Only ordinary sampling from NP2 textures is supported.\n");
                    else np2_fixup = TRUE;
                }
            }
            break;

        case WINED3D_SHADER_RESOURCE_TEXTURE_3D:
            tex_type = "3D";
            break;

        case WINED3D_SHADER_RESOURCE_TEXTURE_CUBE:
            tex_type = "CUBE";
            break;

        default:
            ERR("Unexpected resource type %#x.\n", resource_type);
            tex_type = "";
    }

    /* TEX, TXL, TXD and TXP do not support the "H" modifier,
     * so don't use shader_arb_get_modifier
     */
    if(ins->dst[0].modifiers & WINED3DSPDM_SATURATE) mod = "_SAT";
    else mod = "";

    /* Fragment samplers always have indentity mapping */
    if(sampler_idx >= MAX_FRAGMENT_SAMPLERS)
    {
        sampler_idx = priv->cur_vs_args->vertex.samplers[sampler_idx - MAX_FRAGMENT_SAMPLERS];
    }

    if (pshader)
    {
        masks = calc_color_correction(priv->cur_ps_args->super.color_fixup[sampler_idx],
                ins->dst[0].write_mask);

        if (masks.source || masks.sign)
            tex_dst = "TA";
    }

    if (flags & TEX_DERIV)
    {
        if(flags & TEX_PROJ) FIXME("Projected texture sampling with custom derivatives\n");
        if(flags & TEX_BIAS) FIXME("Biased texture sampling with custom derivatives\n");
        shader_addline(buffer, "TXD%s %s, %s, %s, %s, texture[%u], %s;\n", mod, tex_dst, coord_reg,
                       dsx, dsy, sampler_idx, tex_type);
    }
    else if(flags & TEX_LOD)
    {
        if(flags & TEX_PROJ) FIXME("Projected texture sampling with explicit lod\n");
        if(flags & TEX_BIAS) FIXME("Biased texture sampling with explicit lod\n");
        shader_addline(buffer, "TXL%s %s, %s, texture[%u], %s;\n", mod, tex_dst, coord_reg,
                       sampler_idx, tex_type);
    }
    else if (flags & TEX_BIAS)
    {
        /* Shouldn't be possible, but let's check for it */
        if(flags & TEX_PROJ) FIXME("Biased and Projected texture sampling\n");
        /* TXB takes the 4th component of the source vector automatically, as d3d. Nothing more to do */
        shader_addline(buffer, "TXB%s %s, %s, texture[%u], %s;\n", mod, tex_dst, coord_reg, sampler_idx, tex_type);
    }
    else if (flags & TEX_PROJ)
    {
        shader_addline(buffer, "TXP%s %s, %s, texture[%u], %s;\n", mod, tex_dst, coord_reg, sampler_idx, tex_type);
    }
    else
    {
        if (np2_fixup)
        {
            const unsigned char idx = priv->cur_np2fixup_info->super.idx[sampler_idx];
            shader_addline(buffer, "MUL TA, np2fixup[%u].%s, %s;\n", idx >> 1,
                           (idx % 2) ? "zwxy" : "xyzw", coord_reg);

            shader_addline(buffer, "TEX%s %s, TA, texture[%u], %s;\n", mod, tex_dst, sampler_idx, tex_type);
        }
        else
            shader_addline(buffer, "TEX%s %s, %s, texture[%u], %s;\n", mod, tex_dst, coord_reg, sampler_idx, tex_type);
    }

    if (pshader)
    {
        gen_color_correction(buffer, dst_str, tex_dst,
                arb_get_helper_value(WINED3D_SHADER_TYPE_PIXEL, ARB_ONE),
                arb_get_helper_value(WINED3D_SHADER_TYPE_PIXEL, ARB_TWO),
                priv->cur_ps_args->super.color_fixup[sampler_idx], masks);
    }
}