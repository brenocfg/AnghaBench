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
struct wined3d_texture {int flags; TYPE_1__* sub_resources; } ;
struct wined3d_resource {scalar_t__ type; int access; int map_binding; } ;
struct wined3d_rendertarget_view {size_t sub_resource_idx; struct wined3d_resource* resource; } ;
struct TYPE_2__ {int locations; } ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int WINED3D_LOCATION_DISCARDED ; 
 int WINED3D_RESOURCE_ACCESS_GPU ; 
 scalar_t__ WINED3D_RTYPE_BUFFER ; 
 int WINED3D_TEXTURE_CONVERTED ; 
 int WINED3D_TEXTURE_PIN_SYSMEM ; 
 struct wined3d_texture* texture_from_resource (struct wined3d_resource*) ; 

__attribute__((used)) static BOOL ffp_blitter_use_cpu_clear(struct wined3d_rendertarget_view *view)
{
    struct wined3d_resource *resource;
    struct wined3d_texture *texture;
    DWORD locations;

    resource = view->resource;
    if (resource->type == WINED3D_RTYPE_BUFFER)
        return !(resource->access & WINED3D_RESOURCE_ACCESS_GPU);

    texture = texture_from_resource(resource);
    locations = texture->sub_resources[view->sub_resource_idx].locations;
    if (locations & (resource->map_binding | WINED3D_LOCATION_DISCARDED))
        return !(resource->access & WINED3D_RESOURCE_ACCESS_GPU)
                || (texture->flags & WINED3D_TEXTURE_PIN_SYSMEM);

    return !(resource->access & WINED3D_RESOURCE_ACCESS_GPU)
            && !(texture->flags & WINED3D_TEXTURE_CONVERTED);
}