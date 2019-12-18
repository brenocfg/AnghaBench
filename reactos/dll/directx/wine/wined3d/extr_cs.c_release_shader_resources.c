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
struct wined3d_state {struct wined3d_shader_resource_view*** shader_resource_view; TYPE_1__*** cb; struct wined3d_shader** shader; } ;
struct wined3d_shader_sampler_map_entry {size_t resource_idx; } ;
struct wined3d_shader_resource_view {int /*<<< orphan*/ * resource; } ;
struct TYPE_5__ {unsigned int count; struct wined3d_shader_sampler_map_entry* entries; } ;
struct TYPE_6__ {TYPE_2__ sampler_map; } ;
struct wined3d_shader {TYPE_3__ reg_maps; } ;
struct TYPE_4__ {int /*<<< orphan*/  resource; } ;

/* Variables and functions */
 unsigned int WINED3D_MAX_CBS ; 
 unsigned int WINED3D_SHADER_TYPE_COUNT ; 
 int /*<<< orphan*/  wined3d_resource_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_shader_resources(const struct wined3d_state *state, unsigned int shader_mask)
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
                wined3d_resource_release(&state->cb[i][j]->resource);
        }

        for (j = 0; j < shader->reg_maps.sampler_map.count; ++j)
        {
            entry = &shader->reg_maps.sampler_map.entries[j];

            if (!(view = state->shader_resource_view[i][entry->resource_idx]))
                continue;

            wined3d_resource_release(view->resource);
        }
    }
}