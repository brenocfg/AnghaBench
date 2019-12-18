#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct wined3d_shader_instruction {int flags; TYPE_10__* ctx; TYPE_12__* src; TYPE_4__* dst; } ;
struct shader_glsl_ctx_priv {TYPE_7__* cur_ps_args; } ;
struct glsl_src_param {int /*<<< orphan*/ * param_str; } ;
struct glsl_sample_function {size_t coord_mask; } ;
typedef  enum wined3d_shader_src_modifier { ____Placeholder_wined3d_shader_src_modifier } wined3d_shader_src_modifier ;
typedef  enum wined3d_shader_resource_type { ____Placeholder_wined3d_shader_resource_type } wined3d_shader_resource_type ;
struct TYPE_15__ {int major; int minor; } ;
struct TYPE_23__ {TYPE_8__* resource_info; TYPE_1__ shader_version; } ;
struct TYPE_22__ {int type; } ;
struct TYPE_21__ {size_t tex_transform; } ;
struct TYPE_20__ {TYPE_5__* idx; } ;
struct TYPE_19__ {size_t offset; } ;
struct TYPE_17__ {TYPE_2__* idx; } ;
struct TYPE_18__ {TYPE_3__ reg; } ;
struct TYPE_16__ {size_t offset; } ;
struct TYPE_14__ {int modifiers; size_t swizzle; TYPE_6__ reg; } ;
struct TYPE_13__ {TYPE_9__* reg_maps; struct shader_glsl_ctx_priv* backend_data; } ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 int WINED3DSI_TEXLD_BIAS ; 
 int WINED3DSI_TEXLD_PROJECT ; 
 int WINED3DSPSM_DW ; 
 int WINED3DSPSM_DZ ; 
 size_t WINED3DSP_NOSWIZZLE ; 
 size_t WINED3DSP_WRITEMASK_1 ; 
 size_t WINED3DSP_WRITEMASK_2 ; 
 size_t WINED3DSP_WRITEMASK_3 ; 
 size_t WINED3D_GLSL_SAMPLE_PROJECTED ; 
 size_t WINED3D_PSARGS_PROJECTED ; 
 size_t WINED3D_PSARGS_TEXTRANSFORM_MASK ; 
 size_t WINED3D_PSARGS_TEXTRANSFORM_SHIFT ; 
 int WINED3D_SHADER_RESOURCE_TEXTURE_CUBE ; 
 size_t WINED3D_SHADER_VERSION (int,int) ; 
#define  WINED3D_TTFF_COUNT1 132 
#define  WINED3D_TTFF_COUNT2 131 
#define  WINED3D_TTFF_COUNT3 130 
#define  WINED3D_TTFF_COUNT4 129 
#define  WINED3D_TTFF_DISABLE 128 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,TYPE_12__*,size_t,struct glsl_src_param*) ; 
 int /*<<< orphan*/  shader_glsl_gen_sample_code (struct wined3d_shader_instruction const*,size_t,struct glsl_sample_function*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,size_t,...) ; 
 int /*<<< orphan*/  shader_glsl_get_sample_function (TYPE_10__*,size_t,size_t,size_t,struct glsl_sample_function*) ; 
 int /*<<< orphan*/  shader_glsl_release_sample_function (TYPE_10__*,struct glsl_sample_function*) ; 
 int /*<<< orphan*/  shader_glsl_write_mask_to_str (size_t,char*) ; 

__attribute__((used)) static void shader_glsl_tex(const struct wined3d_shader_instruction *ins)
{
    DWORD shader_version = WINED3D_SHADER_VERSION(ins->ctx->reg_maps->shader_version.major,
            ins->ctx->reg_maps->shader_version.minor);
    struct glsl_sample_function sample_function;
    DWORD sample_flags = 0;
    DWORD resource_idx;
    DWORD mask = 0, swizzle;
    const struct shader_glsl_ctx_priv *priv = ins->ctx->backend_data;

    /* 1.0-1.4: Use destination register as sampler source.
     * 2.0+: Use provided sampler source. */
    if (shader_version < WINED3D_SHADER_VERSION(2,0))
        resource_idx = ins->dst[0].reg.idx[0].offset;
    else
        resource_idx = ins->src[1].reg.idx[0].offset;

    if (shader_version < WINED3D_SHADER_VERSION(1,4))
    {
        DWORD flags = (priv->cur_ps_args->tex_transform >> resource_idx * WINED3D_PSARGS_TEXTRANSFORM_SHIFT)
                & WINED3D_PSARGS_TEXTRANSFORM_MASK;
        enum wined3d_shader_resource_type resource_type = ins->ctx->reg_maps->resource_info[resource_idx].type;

        /* Projected cube textures don't make a lot of sense, the resulting coordinates stay the same. */
        if (flags & WINED3D_PSARGS_PROJECTED && resource_type != WINED3D_SHADER_RESOURCE_TEXTURE_CUBE)
        {
            sample_flags |= WINED3D_GLSL_SAMPLE_PROJECTED;
            switch (flags & ~WINED3D_PSARGS_PROJECTED)
            {
                case WINED3D_TTFF_COUNT1:
                    FIXME("WINED3D_TTFF_PROJECTED with WINED3D_TTFF_COUNT1?\n");
                    break;
                case WINED3D_TTFF_COUNT2:
                    mask = WINED3DSP_WRITEMASK_1;
                    break;
                case WINED3D_TTFF_COUNT3:
                    mask = WINED3DSP_WRITEMASK_2;
                    break;
                case WINED3D_TTFF_COUNT4:
                case WINED3D_TTFF_DISABLE:
                    mask = WINED3DSP_WRITEMASK_3;
                    break;
            }
        }
    }
    else if (shader_version < WINED3D_SHADER_VERSION(2,0))
    {
        enum wined3d_shader_src_modifier src_mod = ins->src[0].modifiers;

        if (src_mod == WINED3DSPSM_DZ) {
            sample_flags |= WINED3D_GLSL_SAMPLE_PROJECTED;
            mask = WINED3DSP_WRITEMASK_2;
        } else if (src_mod == WINED3DSPSM_DW) {
            sample_flags |= WINED3D_GLSL_SAMPLE_PROJECTED;
            mask = WINED3DSP_WRITEMASK_3;
        }
    }
    else
    {
        if ((ins->flags & WINED3DSI_TEXLD_PROJECT)
                && ins->ctx->reg_maps->resource_info[resource_idx].type != WINED3D_SHADER_RESOURCE_TEXTURE_CUBE)
        {
            /* ps 2.0 texldp instruction always divides by the fourth component. */
            sample_flags |= WINED3D_GLSL_SAMPLE_PROJECTED;
            mask = WINED3DSP_WRITEMASK_3;
        }
    }

    shader_glsl_get_sample_function(ins->ctx, resource_idx, resource_idx, sample_flags, &sample_function);
    mask |= sample_function.coord_mask;
    sample_function.coord_mask = mask;

    if (shader_version < WINED3D_SHADER_VERSION(2,0)) swizzle = WINED3DSP_NOSWIZZLE;
    else swizzle = ins->src[1].swizzle;

    /* 1.0-1.3: Use destination register as coordinate source.
       1.4+: Use provided coordinate source register. */
    if (shader_version < WINED3D_SHADER_VERSION(1,4))
    {
        char coord_mask[6];
        shader_glsl_write_mask_to_str(mask, coord_mask);
        shader_glsl_gen_sample_code(ins, resource_idx, &sample_function, swizzle, NULL, NULL, NULL, NULL,
                "T%u%s", resource_idx, coord_mask);
    }
    else
    {
        struct glsl_src_param coord_param;
        shader_glsl_add_src_param(ins, &ins->src[0], mask, &coord_param);
        if (ins->flags & WINED3DSI_TEXLD_BIAS)
        {
            struct glsl_src_param bias;
            shader_glsl_add_src_param(ins, &ins->src[0], WINED3DSP_WRITEMASK_3, &bias);
            shader_glsl_gen_sample_code(ins, resource_idx, &sample_function, swizzle, NULL, NULL, bias.param_str,
                    NULL, "%s", coord_param.param_str);
        } else {
            shader_glsl_gen_sample_code(ins, resource_idx, &sample_function, swizzle, NULL, NULL, NULL, NULL,
                    "%s", coord_param.param_str);
        }
    }
    shader_glsl_release_sample_function(ins->ctx, &sample_function);
}