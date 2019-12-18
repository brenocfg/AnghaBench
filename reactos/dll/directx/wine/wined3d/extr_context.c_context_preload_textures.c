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
struct wined3d_state {TYPE_3__** shader; } ;
struct wined3d_context {int fixed_function_usage_map; } ;
typedef  int WORD ;
struct TYPE_5__ {TYPE_1__* resource_info; } ;
struct TYPE_6__ {TYPE_2__ reg_maps; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 unsigned int MAX_FRAGMENT_SAMPLERS ; 
 unsigned int MAX_VERTEX_SAMPLERS ; 
 size_t WINED3D_SHADER_TYPE_PIXEL ; 
 size_t WINED3D_SHADER_TYPE_VERTEX ; 
 int /*<<< orphan*/  context_preload_texture (struct wined3d_context*,struct wined3d_state const*,unsigned int) ; 
 scalar_t__ use_ps (struct wined3d_state const*) ; 
 scalar_t__ use_vs (struct wined3d_state const*) ; 

__attribute__((used)) static void context_preload_textures(struct wined3d_context *context, const struct wined3d_state *state)
{
    unsigned int i;

    if (use_vs(state))
    {
        for (i = 0; i < MAX_VERTEX_SAMPLERS; ++i)
        {
            if (state->shader[WINED3D_SHADER_TYPE_VERTEX]->reg_maps.resource_info[i].type)
                context_preload_texture(context, state, MAX_FRAGMENT_SAMPLERS + i);
        }
    }

    if (use_ps(state))
    {
        for (i = 0; i < MAX_FRAGMENT_SAMPLERS; ++i)
        {
            if (state->shader[WINED3D_SHADER_TYPE_PIXEL]->reg_maps.resource_info[i].type)
                context_preload_texture(context, state, i);
        }
    }
    else
    {
        WORD ffu_map = context->fixed_function_usage_map;

        for (i = 0; ffu_map; ffu_map >>= 1, ++i)
        {
            if (ffu_map & 1)
                context_preload_texture(context, state, i);
        }
    }
}