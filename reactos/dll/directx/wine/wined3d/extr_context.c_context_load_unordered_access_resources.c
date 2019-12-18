#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wined3d_unordered_access_view {TYPE_1__* resource; } ;
struct wined3d_texture {int dummy; } ;
struct wined3d_shader {int dummy; } ;
struct wined3d_context {int uses_uavs; } ;
struct wined3d_buffer {int dummy; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 unsigned int MAX_UNORDERED_ACCESS_VIEWS ; 
 int /*<<< orphan*/  WINED3D_LOCATION_BUFFER ; 
 int /*<<< orphan*/  WINED3D_LOCATION_TEXTURE_RGB ; 
 scalar_t__ WINED3D_RTYPE_BUFFER ; 
 struct wined3d_buffer* buffer_from_resource (TYPE_1__*) ; 
 struct wined3d_texture* texture_from_resource (TYPE_1__*) ; 
 int /*<<< orphan*/  wined3d_buffer_load_location (struct wined3d_buffer*,struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_load (struct wined3d_texture*,struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_unordered_access_view_invalidate_location (struct wined3d_unordered_access_view*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void context_load_unordered_access_resources(struct wined3d_context *context,
        const struct wined3d_shader *shader, struct wined3d_unordered_access_view * const *views)
{
    struct wined3d_unordered_access_view *view;
    struct wined3d_texture *texture;
    struct wined3d_buffer *buffer;
    unsigned int i;

    context->uses_uavs = 0;

    if (!shader)
        return;

    for (i = 0; i < MAX_UNORDERED_ACCESS_VIEWS; ++i)
    {
        if (!(view = views[i]))
            continue;

        if (view->resource->type == WINED3D_RTYPE_BUFFER)
        {
            buffer = buffer_from_resource(view->resource);
            wined3d_buffer_load_location(buffer, context, WINED3D_LOCATION_BUFFER);
            wined3d_unordered_access_view_invalidate_location(view, ~WINED3D_LOCATION_BUFFER);
        }
        else
        {
            texture = texture_from_resource(view->resource);
            wined3d_texture_load(texture, context, FALSE);
            wined3d_unordered_access_view_invalidate_location(view, ~WINED3D_LOCATION_TEXTURE_RGB);
        }

        context->uses_uavs = 1;
    }
}