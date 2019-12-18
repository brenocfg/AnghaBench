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
struct wined3d_texture {unsigned int level_count; void* rb_resolved; void* rb_multisample; TYPE_4__* sub_resources; } ;
struct wined3d_surface {TYPE_5__* current_renderbuffer; } ;
struct wined3d_resource {scalar_t__ type; TYPE_1__* format; } ;
struct TYPE_8__ {int /*<<< orphan*/  target; void* name; } ;
struct wined3d_rendertarget_info {unsigned int sub_resource_idx; int layer_count; TYPE_2__ gl_view; struct wined3d_resource* resource; } ;
struct wined3d_fbo_entry_key {int rb_namespace; TYPE_6__* objects; } ;
struct wined3d_context {int dummy; } ;
struct TYPE_12__ {unsigned int level; unsigned int layer; int /*<<< orphan*/  target; void* object; } ;
struct TYPE_11__ {void* id; } ;
struct TYPE_9__ {struct wined3d_surface* surface; } ;
struct TYPE_10__ {TYPE_3__ u; } ;
struct TYPE_7__ {scalar_t__ id; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WINED3DFMT_NULL ; 
 void* WINED3D_ALL_LAYERS ; 
#define  WINED3D_LOCATION_RB_MULTISAMPLE 131 
#define  WINED3D_LOCATION_RB_RESOLVED 130 
#define  WINED3D_LOCATION_TEXTURE_RGB 129 
#define  WINED3D_LOCATION_TEXTURE_SRGB 128 
 scalar_t__ WINED3D_RTYPE_BUFFER ; 
 scalar_t__ WINED3D_RTYPE_TEXTURE_2D ; 
 int /*<<< orphan*/  debug_d3dresourcetype (scalar_t__) ; 
 struct wined3d_texture* wined3d_texture_from_resource (struct wined3d_resource*) ; 
 int /*<<< orphan*/  wined3d_texture_get_sub_resource_target (struct wined3d_texture*,unsigned int) ; 
 void* wined3d_texture_get_texture_name (struct wined3d_texture*,struct wined3d_context const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void context_set_fbo_key_for_render_target(const struct wined3d_context *context,
        struct wined3d_fbo_entry_key *key, unsigned int idx, const struct wined3d_rendertarget_info *render_target,
        DWORD location)
{
    unsigned int sub_resource_idx = render_target->sub_resource_idx;
    struct wined3d_resource *resource = render_target->resource;
    struct wined3d_texture *texture;

    if (!resource || resource->format->id == WINED3DFMT_NULL || resource->type == WINED3D_RTYPE_BUFFER)
    {
        if (resource && resource->type == WINED3D_RTYPE_BUFFER)
            FIXME("Not implemented for %s resources.\n", debug_d3dresourcetype(resource->type));
        key->objects[idx].object = 0;
        key->objects[idx].target = 0;
        key->objects[idx].level = key->objects[idx].layer = 0;
        return;
    }

    if (render_target->gl_view.name)
    {
        key->objects[idx].object = render_target->gl_view.name;
        key->objects[idx].target = render_target->gl_view.target;
        key->objects[idx].level = 0;
        key->objects[idx].layer = WINED3D_ALL_LAYERS;
        return;
    }

    texture = wined3d_texture_from_resource(resource);
    if (resource->type == WINED3D_RTYPE_TEXTURE_2D)
    {
        struct wined3d_surface *surface = texture->sub_resources[sub_resource_idx].u.surface;

        if (surface->current_renderbuffer)
        {
            key->objects[idx].object = surface->current_renderbuffer->id;
            key->objects[idx].target = 0;
            key->objects[idx].level = key->objects[idx].layer = 0;
            key->rb_namespace |= 1 << idx;
            return;
        }
    }
    key->objects[idx].target = wined3d_texture_get_sub_resource_target(texture, sub_resource_idx);
    key->objects[idx].level = sub_resource_idx % texture->level_count;
    key->objects[idx].layer = sub_resource_idx / texture->level_count;

    if (render_target->layer_count != 1)
        key->objects[idx].layer = WINED3D_ALL_LAYERS;

    switch (location)
    {
        case WINED3D_LOCATION_TEXTURE_RGB:
            key->objects[idx].object = wined3d_texture_get_texture_name(texture, context, FALSE);
            break;

        case WINED3D_LOCATION_TEXTURE_SRGB:
            key->objects[idx].object = wined3d_texture_get_texture_name(texture, context, TRUE);
            break;

        case WINED3D_LOCATION_RB_MULTISAMPLE:
            key->objects[idx].object = texture->rb_multisample;
            key->objects[idx].target = 0;
            key->objects[idx].level = key->objects[idx].layer = 0;
            key->rb_namespace |= 1 << idx;
            break;

        case WINED3D_LOCATION_RB_RESOLVED:
            key->objects[idx].object = texture->rb_resolved;
            key->objects[idx].target = 0;
            key->objects[idx].level = key->objects[idx].layer = 0;
            key->rb_namespace |= 1 << idx;
            break;
    }
}