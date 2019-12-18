#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wined3d_stream_info {unsigned int use_map; int /*<<< orphan*/  swizzle_map; scalar_t__ position_transformed; } ;
struct wined3d_state {scalar_t__ gl_primitive_type; int* render_states; unsigned int** texture_states; TYPE_3__* transforms; TYPE_2__** lights; } ;
struct wined3d_gl_info {int dummy; } ;
struct wined3d_ffp_vs_settings {int transformed; int point_size; int per_vertex_point_size; unsigned int texcoords; unsigned int* texgen; int flatshading; int vertexblends; int sw_blending; int vb_indices; int clipping; int normal; int normalize; int lighting; int localviewer; int diffuse_source; int emissive_source; int ambient_source; int specular_source; int ortho_fog; int /*<<< orphan*/  swizzle_map; void* fog_mode; int /*<<< orphan*/  parallel_point_light_count; int /*<<< orphan*/  directional_light_count; int /*<<< orphan*/  spot_light_count; int /*<<< orphan*/  point_light_count; } ;
struct TYPE_8__ {scalar_t__ varying_count; } ;
struct wined3d_d3d_info {scalar_t__ emulated_flatshading; TYPE_4__ limits; } ;
struct wined3d_context {int /*<<< orphan*/  device; struct wined3d_d3d_info* d3d_info; struct wined3d_gl_info* gl_info; struct wined3d_stream_info stream_info; } ;
struct TYPE_7__ {float _14; float _24; float _34; float _44; } ;
struct TYPE_5__ {int type; } ;
struct TYPE_6__ {TYPE_1__ OriginalParms; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 scalar_t__ GL_POINTS ; 
 unsigned int MAX_ACTIVE_LIGHTS ; 
 unsigned int MAX_TEXTURES ; 
 unsigned int WINED3D_FFP_DIFFUSE ; 
 unsigned int WINED3D_FFP_NORMAL ; 
 unsigned int WINED3D_FFP_PSIZE ; 
 unsigned int WINED3D_FFP_TEXCOORD0 ; 
 void* WINED3D_FFP_VS_FOG_DEPTH ; 
 void* WINED3D_FFP_VS_FOG_FOGCOORD ; 
 void* WINED3D_FFP_VS_FOG_OFF ; 
 void* WINED3D_FFP_VS_FOG_RANGE ; 
 int WINED3D_FOG_NONE ; 
#define  WINED3D_LIGHT_DIRECTIONAL 135 
#define  WINED3D_LIGHT_PARALLELPOINT 134 
#define  WINED3D_LIGHT_POINT 133 
#define  WINED3D_LIGHT_SPOT 132 
 void* WINED3D_MCS_MATERIAL ; 
 size_t WINED3D_RS_AMBIENTMATERIALSOURCE ; 
 size_t WINED3D_RS_CLIPPING ; 
 size_t WINED3D_RS_CLIPPLANEENABLE ; 
 size_t WINED3D_RS_COLORVERTEX ; 
 size_t WINED3D_RS_DIFFUSEMATERIALSOURCE ; 
 size_t WINED3D_RS_EMISSIVEMATERIALSOURCE ; 
 size_t WINED3D_RS_FOGENABLE ; 
 size_t WINED3D_RS_FOGTABLEMODE ; 
 size_t WINED3D_RS_FOGVERTEXMODE ; 
 size_t WINED3D_RS_LIGHTING ; 
 size_t WINED3D_RS_LOCALVIEWER ; 
 size_t WINED3D_RS_NORMALIZENORMALS ; 
 size_t WINED3D_RS_RANGEFOGENABLE ; 
 size_t WINED3D_RS_SHADEMODE ; 
 size_t WINED3D_RS_SPECULARMATERIALSOURCE ; 
 size_t WINED3D_RS_VERTEXBLEND ; 
 int WINED3D_SHADE_FLAT ; 
 size_t WINED3D_TSS_TEXCOORD_INDEX ; 
 size_t WINED3D_TS_PROJECTION ; 
#define  WINED3D_VBF_1WEIGHTS 131 
#define  WINED3D_VBF_2WEIGHTS 130 
#define  WINED3D_VBF_3WEIGHTS 129 
#define  WINED3D_VBF_DISABLE 128 
 int /*<<< orphan*/  memset (struct wined3d_ffp_vs_settings*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ use_indexed_vertex_blending (struct wined3d_state const*,struct wined3d_stream_info const*) ; 
 scalar_t__ use_software_vertex_processing (int /*<<< orphan*/ ) ; 
 scalar_t__ wined3d_max_compat_varyings (struct wined3d_gl_info const*) ; 

void wined3d_ffp_get_vs_settings(const struct wined3d_context *context,
        const struct wined3d_state *state, struct wined3d_ffp_vs_settings *settings)
{
    const struct wined3d_stream_info *si = &context->stream_info;
    const struct wined3d_gl_info *gl_info = context->gl_info;
    const struct wined3d_d3d_info *d3d_info = context->d3d_info;
    unsigned int coord_idx, i;

    memset(settings, 0, sizeof(*settings));

    if (si->position_transformed)
    {
        settings->transformed = 1;
        settings->point_size = state->gl_primitive_type == GL_POINTS;
        settings->per_vertex_point_size = !!(si->use_map & 1u << WINED3D_FFP_PSIZE);
        if (!state->render_states[WINED3D_RS_FOGENABLE])
            settings->fog_mode = WINED3D_FFP_VS_FOG_OFF;
        else if (state->render_states[WINED3D_RS_FOGTABLEMODE] != WINED3D_FOG_NONE)
            settings->fog_mode = WINED3D_FFP_VS_FOG_DEPTH;
        else
            settings->fog_mode = WINED3D_FFP_VS_FOG_FOGCOORD;

        for (i = 0; i < MAX_TEXTURES; ++i)
        {
            coord_idx = state->texture_states[i][WINED3D_TSS_TEXCOORD_INDEX];
            if (coord_idx < MAX_TEXTURES && (si->use_map & (1u << (WINED3D_FFP_TEXCOORD0 + coord_idx))))
                settings->texcoords |= 1u << i;
            settings->texgen[i] = state->texture_states[i][WINED3D_TSS_TEXCOORD_INDEX];
        }
        if (d3d_info->limits.varying_count >= wined3d_max_compat_varyings(gl_info))
            settings->texcoords = (1u << MAX_TEXTURES) - 1;

        if (d3d_info->emulated_flatshading)
            settings->flatshading = state->render_states[WINED3D_RS_SHADEMODE] == WINED3D_SHADE_FLAT;
        else
            settings->flatshading = FALSE;

        settings->swizzle_map = si->swizzle_map;

        return;
    }

    switch (state->render_states[WINED3D_RS_VERTEXBLEND])
    {
        case WINED3D_VBF_DISABLE:
        case WINED3D_VBF_1WEIGHTS:
        case WINED3D_VBF_2WEIGHTS:
        case WINED3D_VBF_3WEIGHTS:
            settings->vertexblends = state->render_states[WINED3D_RS_VERTEXBLEND];
            break;
        default:
            FIXME("Unsupported vertex blending: %d\n", state->render_states[WINED3D_RS_VERTEXBLEND]);
            break;
    }

    if (use_indexed_vertex_blending(state, si))
    {
        if (use_software_vertex_processing(context->device))
            settings->sw_blending = 1;
        else
            settings->vb_indices = 1;
    }

    settings->clipping = state->render_states[WINED3D_RS_CLIPPING]
            && state->render_states[WINED3D_RS_CLIPPLANEENABLE];
    settings->normal = !!(si->use_map & (1u << WINED3D_FFP_NORMAL));
    settings->normalize = settings->normal && state->render_states[WINED3D_RS_NORMALIZENORMALS];
    settings->lighting = !!state->render_states[WINED3D_RS_LIGHTING];
    settings->localviewer = !!state->render_states[WINED3D_RS_LOCALVIEWER];
    settings->point_size = state->gl_primitive_type == GL_POINTS;
    settings->per_vertex_point_size = !!(si->use_map & 1u << WINED3D_FFP_PSIZE);

    if (state->render_states[WINED3D_RS_COLORVERTEX] && (si->use_map & (1u << WINED3D_FFP_DIFFUSE)))
    {
        settings->diffuse_source = state->render_states[WINED3D_RS_DIFFUSEMATERIALSOURCE];
        settings->emissive_source = state->render_states[WINED3D_RS_EMISSIVEMATERIALSOURCE];
        settings->ambient_source = state->render_states[WINED3D_RS_AMBIENTMATERIALSOURCE];
        settings->specular_source = state->render_states[WINED3D_RS_SPECULARMATERIALSOURCE];
    }
    else
    {
        settings->diffuse_source = WINED3D_MCS_MATERIAL;
        settings->emissive_source = WINED3D_MCS_MATERIAL;
        settings->ambient_source = WINED3D_MCS_MATERIAL;
        settings->specular_source = WINED3D_MCS_MATERIAL;
    }

    for (i = 0; i < MAX_TEXTURES; ++i)
    {
        coord_idx = state->texture_states[i][WINED3D_TSS_TEXCOORD_INDEX];
        if (coord_idx < MAX_TEXTURES && (si->use_map & (1u << (WINED3D_FFP_TEXCOORD0 + coord_idx))))
            settings->texcoords |= 1u << i;
        settings->texgen[i] = state->texture_states[i][WINED3D_TSS_TEXCOORD_INDEX];
    }
    if (d3d_info->limits.varying_count >= wined3d_max_compat_varyings(gl_info))
        settings->texcoords = (1u << MAX_TEXTURES) - 1;

    for (i = 0; i < MAX_ACTIVE_LIGHTS; ++i)
    {
        if (!state->lights[i])
            continue;

        switch (state->lights[i]->OriginalParms.type)
        {
            case WINED3D_LIGHT_POINT:
                ++settings->point_light_count;
                break;
            case WINED3D_LIGHT_SPOT:
                ++settings->spot_light_count;
                break;
            case WINED3D_LIGHT_DIRECTIONAL:
                ++settings->directional_light_count;
                break;
            case WINED3D_LIGHT_PARALLELPOINT:
                ++settings->parallel_point_light_count;
                break;
            default:
                FIXME("Unhandled light type %#x.\n", state->lights[i]->OriginalParms.type);
                break;
        }
    }

    if (!state->render_states[WINED3D_RS_FOGENABLE])
        settings->fog_mode = WINED3D_FFP_VS_FOG_OFF;
    else if (state->render_states[WINED3D_RS_FOGTABLEMODE] != WINED3D_FOG_NONE)
    {
        settings->fog_mode = WINED3D_FFP_VS_FOG_DEPTH;

        if (state->transforms[WINED3D_TS_PROJECTION]._14 == 0.0f
                && state->transforms[WINED3D_TS_PROJECTION]._24 == 0.0f
                && state->transforms[WINED3D_TS_PROJECTION]._34 == 0.0f
                && state->transforms[WINED3D_TS_PROJECTION]._44 == 1.0f)
            settings->ortho_fog = 1;
    }
    else if (state->render_states[WINED3D_RS_FOGVERTEXMODE] == WINED3D_FOG_NONE)
        settings->fog_mode = WINED3D_FFP_VS_FOG_FOGCOORD;
    else if (state->render_states[WINED3D_RS_RANGEFOGENABLE])
        settings->fog_mode = WINED3D_FFP_VS_FOG_RANGE;
    else
        settings->fog_mode = WINED3D_FFP_VS_FOG_DEPTH;

    if (d3d_info->emulated_flatshading)
        settings->flatshading = state->render_states[WINED3D_RS_SHADEMODE] == WINED3D_SHADE_FLAT;
    else
        settings->flatshading = FALSE;

    settings->swizzle_map = si->swizzle_map;
}