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
struct wined3d_texture_sub_resource {int dummy; } ;
struct wined3d_surface {TYPE_1__* container; } ;
struct TYPE_2__ {struct wined3d_texture_sub_resource* sub_resources; } ;

/* Variables and functions */
 size_t surface_get_sub_resource_idx (struct wined3d_surface*) ; 

__attribute__((used)) static inline struct wined3d_texture_sub_resource *surface_get_sub_resource(struct wined3d_surface *surface)
{
    return &surface->container->sub_resources[surface_get_sub_resource_idx(surface)];
}