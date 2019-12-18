#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int* renderState; int* transform; unsigned int vertexShaderConstantsI; unsigned int vertexShaderConstantsB; unsigned int pixelShaderConstantsI; unsigned int pixelShaderConstantsB; int* textureState; int* samplerState; scalar_t__* ps_consts_f; scalar_t__* vs_consts_f; } ;
struct wined3d_stateblock {unsigned int* contained_render_states; size_t num_contained_render_states; unsigned int* contained_transform_states; size_t num_contained_transform_states; unsigned int* contained_vs_consts_f; size_t num_contained_vs_consts_f; unsigned int* contained_vs_consts_i; size_t num_contained_vs_consts_i; unsigned int* contained_vs_consts_b; size_t num_contained_vs_consts_b; unsigned int* contained_ps_consts_f; size_t num_contained_ps_consts_f; unsigned int* contained_ps_consts_i; size_t num_contained_ps_consts_i; unsigned int* contained_ps_consts_b; size_t num_contained_ps_consts_b; size_t num_contained_tss_states; size_t num_contained_sampler_states; TYPE_6__* contained_sampler_states; TYPE_5__ changed; TYPE_4__* contained_tss_states; TYPE_2__* device; } ;
struct TYPE_9__ {unsigned int vs_uniform_count; unsigned int ps_uniform_count; } ;
struct wined3d_d3d_info {TYPE_3__ limits; } ;
struct TYPE_12__ {unsigned int stage; unsigned int state; } ;
struct TYPE_10__ {unsigned int stage; unsigned int state; } ;
struct TYPE_8__ {TYPE_1__* adapter; } ;
struct TYPE_7__ {struct wined3d_d3d_info d3d_info; } ;
typedef  int DWORD ;

/* Variables and functions */
 unsigned int HIGHEST_TRANSFORMSTATE ; 
 unsigned int MAX_COMBINED_SAMPLERS ; 
 unsigned int MAX_TEXTURES ; 
 unsigned int WINED3D_MAX_CONSTS_B ; 
 unsigned int WINED3D_MAX_CONSTS_I ; 
 unsigned int WINEHIGHEST_RENDER_STATE ; 

void stateblock_init_contained_states(struct wined3d_stateblock *stateblock)
{
    const struct wined3d_d3d_info *d3d_info = &stateblock->device->adapter->d3d_info;
    unsigned int i, j;

    for (i = 0; i <= WINEHIGHEST_RENDER_STATE >> 5; ++i)
    {
        DWORD map = stateblock->changed.renderState[i];
        for (j = 0; map; map >>= 1, ++j)
        {
            if (!(map & 1)) continue;

            stateblock->contained_render_states[stateblock->num_contained_render_states] = (i << 5) | j;
            ++stateblock->num_contained_render_states;
        }
    }

    for (i = 0; i <= HIGHEST_TRANSFORMSTATE >> 5; ++i)
    {
        DWORD map = stateblock->changed.transform[i];
        for (j = 0; map; map >>= 1, ++j)
        {
            if (!(map & 1)) continue;

            stateblock->contained_transform_states[stateblock->num_contained_transform_states] = (i << 5) | j;
            ++stateblock->num_contained_transform_states;
        }
    }

    for (i = 0; i < d3d_info->limits.vs_uniform_count; ++i)
    {
        if (stateblock->changed.vs_consts_f[i])
        {
            stateblock->contained_vs_consts_f[stateblock->num_contained_vs_consts_f] = i;
            ++stateblock->num_contained_vs_consts_f;
        }
    }

    for (i = 0; i < WINED3D_MAX_CONSTS_I; ++i)
    {
        if (stateblock->changed.vertexShaderConstantsI & (1u << i))
        {
            stateblock->contained_vs_consts_i[stateblock->num_contained_vs_consts_i] = i;
            ++stateblock->num_contained_vs_consts_i;
        }
    }

    for (i = 0; i < WINED3D_MAX_CONSTS_B; ++i)
    {
        if (stateblock->changed.vertexShaderConstantsB & (1u << i))
        {
            stateblock->contained_vs_consts_b[stateblock->num_contained_vs_consts_b] = i;
            ++stateblock->num_contained_vs_consts_b;
        }
    }

    for (i = 0; i < d3d_info->limits.ps_uniform_count; ++i)
    {
        if (stateblock->changed.ps_consts_f[i])
        {
            stateblock->contained_ps_consts_f[stateblock->num_contained_ps_consts_f] = i;
            ++stateblock->num_contained_ps_consts_f;
        }
    }

    for (i = 0; i < WINED3D_MAX_CONSTS_I; ++i)
    {
        if (stateblock->changed.pixelShaderConstantsI & (1u << i))
        {
            stateblock->contained_ps_consts_i[stateblock->num_contained_ps_consts_i] = i;
            ++stateblock->num_contained_ps_consts_i;
        }
    }

    for (i = 0; i < WINED3D_MAX_CONSTS_B; ++i)
    {
        if (stateblock->changed.pixelShaderConstantsB & (1u << i))
        {
            stateblock->contained_ps_consts_b[stateblock->num_contained_ps_consts_b] = i;
            ++stateblock->num_contained_ps_consts_b;
        }
    }

    for (i = 0; i < MAX_TEXTURES; ++i)
    {
        DWORD map = stateblock->changed.textureState[i];

        for(j = 0; map; map >>= 1, ++j)
        {
            if (!(map & 1)) continue;

            stateblock->contained_tss_states[stateblock->num_contained_tss_states].stage = i;
            stateblock->contained_tss_states[stateblock->num_contained_tss_states].state = j;
            ++stateblock->num_contained_tss_states;
        }
    }

    for (i = 0; i < MAX_COMBINED_SAMPLERS; ++i)
    {
        DWORD map = stateblock->changed.samplerState[i];

        for (j = 0; map; map >>= 1, ++j)
        {
            if (!(map & 1)) continue;

            stateblock->contained_sampler_states[stateblock->num_contained_sampler_states].stage = i;
            stateblock->contained_sampler_states[stateblock->num_contained_sampler_states].state = j;
            ++stateblock->num_contained_sampler_states;
        }
    }
}