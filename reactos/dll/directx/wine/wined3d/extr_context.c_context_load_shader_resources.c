#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wined3d_state {struct wined3d_shader_resource_view*** shader_resource_view; scalar_t__** cb; struct wined3d_shader** shader; } ;
struct wined3d_shader_sampler_map_entry {size_t resource_idx; } ;
struct wined3d_shader_resource_view {TYPE_3__* resource; } ;
struct TYPE_5__ {unsigned int count; struct wined3d_shader_sampler_map_entry* entries; } ;
struct TYPE_6__ {TYPE_1__ sampler_map; } ;
struct wined3d_shader {TYPE_2__ reg_maps; } ;
struct wined3d_context {int dummy; } ;
struct TYPE_7__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 unsigned int WINED3D_MAX_CBS ; 
 scalar_t__ WINED3D_RTYPE_BUFFER ; 
 unsigned int WINED3D_SHADER_TYPE_COUNT ; 
 scalar_t__ buffer_from_resource (TYPE_3__*) ; 
 int /*<<< orphan*/  texture_from_resource (TYPE_3__*) ; 
 int /*<<< orphan*/  wined3d_buffer_load (scalar_t__,struct wined3d_context*,struct wined3d_state const*) ; 
 int /*<<< orphan*/  wined3d_texture_load (int /*<<< orphan*/ ,struct wined3d_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void context_load_shader_resources(struct wined3d_context *context, const struct wined3d_state *state,
        unsigned int shader_mask)
{
    struct wined3d_shader_sampler_map_entry *entry;
    struct wined3d_shader_resource_view *view;
    struct wined3d_shader *shader;
    unsigned int i, j;

    for (i = 0; i < WINED3D_SHADER_TYPE_COUNT; ++i)
    {
        if (!(shader_mask & (1u << i)))
            continue;

        if (!(shader = state->shader[i]))
            continue;

        for (j = 0; j < WINED3D_MAX_CBS; ++j)
        {
            if (state->cb[i][j])
                wined3d_buffer_load(state->cb[i][j], context, state);
        }

        for (j = 0; j < shader->reg_maps.sampler_map.count; ++j)
        {
            entry = &shader->reg_maps.sampler_map.entries[j];

            if (!(view = state->shader_resource_view[i][entry->resource_idx]))
                continue;

            if (view->resource->type == WINED3D_RTYPE_BUFFER)
                wined3d_buffer_load(buffer_from_resource(view->resource), context, state);
            else
                wined3d_texture_load(texture_from_resource(view->resource), context, FALSE);
        }
    }
}