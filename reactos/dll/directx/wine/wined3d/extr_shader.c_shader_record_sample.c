#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wined3d_shader_sampler_map_entry {unsigned int resource_idx; unsigned int sampler_idx; unsigned int bind_idx; } ;
struct wined3d_shader_sampler_map {unsigned int count; int size; struct wined3d_shader_sampler_map_entry* entries; } ;
struct wined3d_shader_reg_maps {struct wined3d_shader_sampler_map sampler_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 struct wined3d_shader_sampler_map_entry* heap_calloc (int,int) ; 
 struct wined3d_shader_sampler_map_entry* heap_realloc (struct wined3d_shader_sampler_map_entry*,int) ; 

__attribute__((used)) static void shader_record_sample(struct wined3d_shader_reg_maps *reg_maps,
        unsigned int resource_idx, unsigned int sampler_idx, unsigned int bind_idx)
{
    struct wined3d_shader_sampler_map_entry *entries, *entry;
    struct wined3d_shader_sampler_map *map;
    unsigned int i;

    map = &reg_maps->sampler_map;
    entries = map->entries;
    for (i = 0; i < map->count; ++i)
    {
        if (entries[i].resource_idx == resource_idx && entries[i].sampler_idx == sampler_idx)
            return;
    }

    if (!map->size)
    {
        if (!(entries = heap_calloc(4, sizeof(*entries))))
        {
            ERR("Failed to allocate sampler map entries.\n");
            return;
        }
        map->size = 4;
        map->entries = entries;
    }
    else if (map->count == map->size)
    {
        size_t new_size = map->size * 2;

        if (sizeof(*entries) * new_size <= sizeof(*entries) * map->size
                || !(entries = heap_realloc(entries, sizeof(*entries) * new_size)))
        {
            ERR("Failed to resize sampler map entries.\n");
            return;
        }
        map->size = new_size;
        map->entries = entries;
    }

    entry = &entries[map->count++];
    entry->resource_idx = resource_idx;
    entry->sampler_idx = sampler_idx;
    entry->bind_idx = bind_idx;
}