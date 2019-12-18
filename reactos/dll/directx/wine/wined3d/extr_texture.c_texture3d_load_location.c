#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wined3d_texture_sub_resource {int locations; TYPE_2__* buffer; int /*<<< orphan*/  buffer_object; int /*<<< orphan*/  offset; } ;
struct TYPE_3__ {int /*<<< orphan*/ * heap_memory; } ;
struct wined3d_texture {int /*<<< orphan*/  download_count; TYPE_1__ resource; struct wined3d_texture_sub_resource* sub_resources; } ;
struct wined3d_context {int dummy; } ;
struct wined3d_const_bo_address {int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; int /*<<< orphan*/  addr; } ;
struct wined3d_bo_address {int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ,...) ; 
 int TRUE ; 
#define  WINED3D_LOCATION_BUFFER 131 
#define  WINED3D_LOCATION_SYSMEM 130 
#define  WINED3D_LOCATION_TEXTURE_RGB 129 
#define  WINED3D_LOCATION_TEXTURE_SRGB 128 
 int /*<<< orphan*/  texture3d_download_data (struct wined3d_texture*,unsigned int,struct wined3d_context*,struct wined3d_bo_address*) ; 
 int /*<<< orphan*/  texture3d_srgb_transfer (struct wined3d_texture*,unsigned int,struct wined3d_context*,int) ; 
 int /*<<< orphan*/  texture3d_upload_data (struct wined3d_texture*,unsigned int,struct wined3d_context*,int /*<<< orphan*/ *,struct wined3d_const_bo_address*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  wined3d_debug_location (int) ; 
 int /*<<< orphan*/  wined3d_texture_bind_and_dirtify (struct wined3d_texture*,struct wined3d_context*,int) ; 
 int /*<<< orphan*/  wined3d_texture_get_pitch (struct wined3d_texture*,unsigned int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  wined3d_texture_prepare_location (struct wined3d_texture*,unsigned int,struct wined3d_context*,int) ; 

__attribute__((used)) static BOOL texture3d_load_location(struct wined3d_texture *texture, unsigned int sub_resource_idx,
        struct wined3d_context *context, DWORD location)
{
    struct wined3d_texture_sub_resource *sub_resource = &texture->sub_resources[sub_resource_idx];
    unsigned int row_pitch, slice_pitch;

    if (!wined3d_texture_prepare_location(texture, sub_resource_idx, context, location))
        return FALSE;

    switch (location)
    {
        case WINED3D_LOCATION_TEXTURE_RGB:
        case WINED3D_LOCATION_TEXTURE_SRGB:
            if (sub_resource->locations & WINED3D_LOCATION_SYSMEM)
            {
                struct wined3d_const_bo_address data = {0, texture->resource.heap_memory};
                data.addr += sub_resource->offset;
                wined3d_texture_bind_and_dirtify(texture, context,
                        location == WINED3D_LOCATION_TEXTURE_SRGB);
                wined3d_texture_get_pitch(texture, sub_resource_idx, &row_pitch, &slice_pitch);
                texture3d_upload_data(texture, sub_resource_idx, context, NULL, &data, row_pitch, slice_pitch);
            }
            else if (sub_resource->locations & WINED3D_LOCATION_BUFFER)
            {
#if !defined(STAGING_CSMT)
                struct wined3d_const_bo_address data = {sub_resource->buffer_object, NULL};
#else  /* STAGING_CSMT */
                struct wined3d_const_bo_address data = {sub_resource->buffer->name, NULL};
#endif /* STAGING_CSMT */
                wined3d_texture_bind_and_dirtify(texture, context,
                        location == WINED3D_LOCATION_TEXTURE_SRGB);
                wined3d_texture_get_pitch(texture, sub_resource_idx, &row_pitch, &slice_pitch);
                texture3d_upload_data(texture, sub_resource_idx, context, NULL, &data, row_pitch, slice_pitch);
            }
            else if (sub_resource->locations & WINED3D_LOCATION_TEXTURE_RGB)
            {
                texture3d_srgb_transfer(texture, sub_resource_idx, context, TRUE);
            }
            else if (sub_resource->locations & WINED3D_LOCATION_TEXTURE_SRGB)
            {
                texture3d_srgb_transfer(texture, sub_resource_idx, context, FALSE);
            }
            else
            {
                FIXME("Implement texture loading from %s.\n", wined3d_debug_location(sub_resource->locations));
                return FALSE;
            }
            break;

        case WINED3D_LOCATION_SYSMEM:
            if (sub_resource->locations & (WINED3D_LOCATION_TEXTURE_RGB | WINED3D_LOCATION_TEXTURE_SRGB))
            {
                struct wined3d_bo_address data = {0, texture->resource.heap_memory};

                data.addr += sub_resource->offset;
                if (sub_resource->locations & WINED3D_LOCATION_TEXTURE_RGB)
                    wined3d_texture_bind_and_dirtify(texture, context, FALSE);
                else
                    wined3d_texture_bind_and_dirtify(texture, context, TRUE);

                texture3d_download_data(texture, sub_resource_idx, context, &data);
                ++texture->download_count;
            }
            else
            {
                FIXME("Implement WINED3D_LOCATION_SYSMEM loading from %s.\n",
                        wined3d_debug_location(sub_resource->locations));
                return FALSE;
            }
            break;

        case WINED3D_LOCATION_BUFFER:
            if (sub_resource->locations & (WINED3D_LOCATION_TEXTURE_RGB | WINED3D_LOCATION_TEXTURE_SRGB))
            {
#if !defined(STAGING_CSMT)
                struct wined3d_bo_address data = {sub_resource->buffer_object, NULL};
#else  /* STAGING_CSMT */
                struct wined3d_bo_address data = {sub_resource->buffer->name, NULL};
#endif /* STAGING_CSMT */

                if (sub_resource->locations & WINED3D_LOCATION_TEXTURE_RGB)
                    wined3d_texture_bind_and_dirtify(texture, context, FALSE);
                else
                    wined3d_texture_bind_and_dirtify(texture, context, TRUE);

                texture3d_download_data(texture, sub_resource_idx, context, &data);
            }
            else
            {
                FIXME("Implement WINED3D_LOCATION_BUFFER loading from %s.\n",
                        wined3d_debug_location(sub_resource->locations));
                return FALSE;
            }
            break;

        default:
            FIXME("Implement %s loading from %s.\n", wined3d_debug_location(location),
                    wined3d_debug_location(sub_resource->locations));
            return FALSE;
    }

    return TRUE;
}