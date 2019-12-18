#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  map_count; } ;
struct wined3d_texture {TYPE_1__ resource; int /*<<< orphan*/  update_map_binding; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  wined3d_texture_update_map_binding (struct wined3d_texture*) ; 

void wined3d_texture_set_map_binding(struct wined3d_texture *texture, DWORD map_binding)
{
    texture->update_map_binding = map_binding;
    if (!texture->resource.map_count)
        wined3d_texture_update_map_binding(texture);
}