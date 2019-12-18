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
struct wined3d_surface {int texture_layer; unsigned int texture_level; TYPE_1__* container; } ;
struct TYPE_2__ {int level_count; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int surface_get_sub_resource_idx(const struct wined3d_surface *surface)
{
    return surface->texture_layer * surface->container->level_count + surface->texture_level;
}