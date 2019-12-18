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
struct wined3d_texture {unsigned int level_count; } ;
struct wined3d_resource {scalar_t__ type; } ;
struct TYPE_2__ {int /*<<< orphan*/  slice_pitch; int /*<<< orphan*/  row_pitch; int /*<<< orphan*/  data; } ;
struct wined3d_box {unsigned int right; unsigned int bottom; unsigned int back; int /*<<< orphan*/  front; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct wined3d_cs_update_sub_resource {unsigned int sub_resource_idx; TYPE_1__ data; struct wined3d_box box; struct wined3d_resource* resource; } ;
struct wined3d_cs {int /*<<< orphan*/  device; } ;
struct wined3d_context {int dummy; } ;
struct wined3d_const_bo_address {int /*<<< orphan*/  addr; scalar_t__ buffer_object; } ;
struct wined3d_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  WINED3D_LOCATION_BUFFER ; 
 int /*<<< orphan*/  WINED3D_LOCATION_TEXTURE_RGB ; 
 scalar_t__ WINED3D_RTYPE_BUFFER ; 
 struct wined3d_buffer* buffer_from_resource (struct wined3d_resource*) ; 
 struct wined3d_context* context_acquire (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_release (struct wined3d_context*) ; 
 int /*<<< orphan*/  wined3d_buffer_invalidate_location (struct wined3d_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_buffer_load_location (struct wined3d_buffer*,struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_buffer_upload_data (struct wined3d_buffer*,struct wined3d_context*,struct wined3d_box const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_resource_release (struct wined3d_resource*) ; 
 int /*<<< orphan*/  wined3d_texture_bind_and_dirtify (struct wined3d_texture*,struct wined3d_context*,int /*<<< orphan*/ ) ; 
 struct wined3d_texture* wined3d_texture_from_resource (struct wined3d_resource*) ; 
 unsigned int wined3d_texture_get_level_depth (struct wined3d_texture*,unsigned int) ; 
 unsigned int wined3d_texture_get_level_height (struct wined3d_texture*,unsigned int) ; 
 unsigned int wined3d_texture_get_level_width (struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  wined3d_texture_invalidate_location (struct wined3d_texture*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_load_location (struct wined3d_texture*,unsigned int,struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_prepare_texture (struct wined3d_texture*,struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_upload_data (struct wined3d_texture*,unsigned int,struct wined3d_context*,struct wined3d_box const*,struct wined3d_const_bo_address*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_validate_location (struct wined3d_texture*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wined3d_cs_exec_update_sub_resource(struct wined3d_cs *cs, const void *data)
{
    const struct wined3d_cs_update_sub_resource *op = data;
    struct wined3d_resource *resource = op->resource;
    const struct wined3d_box *box = &op->box;
    unsigned int width, height, depth, level;
    struct wined3d_const_bo_address addr;
    struct wined3d_context *context;
    struct wined3d_texture *texture;

    context = context_acquire(cs->device, NULL, 0);

    if (resource->type == WINED3D_RTYPE_BUFFER)
    {
        struct wined3d_buffer *buffer = buffer_from_resource(resource);

        if (!wined3d_buffer_load_location(buffer, context, WINED3D_LOCATION_BUFFER))
        {
            ERR("Failed to load buffer location.\n");
            goto done;
        }

        wined3d_buffer_upload_data(buffer, context, box, op->data.data);
        wined3d_buffer_invalidate_location(buffer, ~WINED3D_LOCATION_BUFFER);
        goto done;
    }

    texture = wined3d_texture_from_resource(resource);

    level = op->sub_resource_idx % texture->level_count;
    width = wined3d_texture_get_level_width(texture, level);
    height = wined3d_texture_get_level_height(texture, level);
    depth = wined3d_texture_get_level_depth(texture, level);

    addr.buffer_object = 0;
    addr.addr = op->data.data;

    /* Only load the sub-resource for partial updates. */
    if (!box->left && !box->top && !box->front
            && box->right == width && box->bottom == height && box->back == depth)
        wined3d_texture_prepare_texture(texture, context, FALSE);
    else
        wined3d_texture_load_location(texture, op->sub_resource_idx, context, WINED3D_LOCATION_TEXTURE_RGB);
    wined3d_texture_bind_and_dirtify(texture, context, FALSE);

    wined3d_texture_upload_data(texture, op->sub_resource_idx, context,
            box, &addr, op->data.row_pitch, op->data.slice_pitch);

    wined3d_texture_validate_location(texture, op->sub_resource_idx, WINED3D_LOCATION_TEXTURE_RGB);
    wined3d_texture_invalidate_location(texture, op->sub_resource_idx, ~WINED3D_LOCATION_TEXTURE_RGB);

done:
    context_release(context);

    wined3d_resource_release(resource);
}