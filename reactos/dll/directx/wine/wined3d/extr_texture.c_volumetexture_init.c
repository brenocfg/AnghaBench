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
struct wined3d_texture_sub_resource {int /*<<< orphan*/ * parent; int /*<<< orphan*/  parent_ops; int /*<<< orphan*/  locations; } ;
struct TYPE_6__ {int /*<<< orphan*/  map_binding; } ;
struct wined3d_texture {float* pow2_matrix; unsigned int level_count; struct wined3d_texture_sub_resource* sub_resources; TYPE_3__ resource; int /*<<< orphan*/  target; } ;
struct wined3d_resource_desc {scalar_t__ format; int usage; int /*<<< orphan*/  depth; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  access; } ;
struct wined3d_parent_ops {int dummy; } ;
struct wined3d_gl_info {int /*<<< orphan*/ * supported; } ;
struct wined3d_device_parent {TYPE_2__* ops; } ;
struct wined3d_device {TYPE_1__* adapter; struct wined3d_device_parent* device_parent; } ;
typedef  int UINT ;
struct TYPE_5__ {struct wined3d_texture* (* volume_created ) (struct wined3d_device_parent*,struct wined3d_texture*,unsigned int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {struct wined3d_gl_info gl_info; } ;
typedef  struct wined3d_texture* HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 size_t ARB_TEXTURE_NON_POWER_OF_TWO ; 
 int /*<<< orphan*/  ERR (char*) ; 
 size_t EXT_TEXTURE3D ; 
 struct wined3d_texture* E_INVALIDARG ; 
 scalar_t__ FAILED (struct wined3d_texture*) ; 
 int /*<<< orphan*/  GL_TEXTURE_3D ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int,...) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 struct wined3d_texture* WINED3DERR_INVALIDCALL ; 
 scalar_t__ WINED3DFMT_UNKNOWN ; 
 int WINED3DUSAGE_DYNAMIC ; 
 int WINED3DUSAGE_SCRATCH ; 
 int /*<<< orphan*/  WINED3D_LOCATION_BUFFER ; 
 int /*<<< orphan*/  WINED3D_LOCATION_DISCARDED ; 
 struct wined3d_texture* WINED3D_OK ; 
 int /*<<< orphan*/  is_power_of_two (int /*<<< orphan*/ ) ; 
 struct wined3d_texture* stub1 (struct wined3d_device_parent*,struct wined3d_texture*,unsigned int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  texture3d_ops ; 
 int /*<<< orphan*/  texture_resource_ops ; 
 struct wined3d_texture* wined3d_debug_resource_access (int /*<<< orphan*/ ) ; 
 scalar_t__ wined3d_resource_access_is_managed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_resource_free_sysmem (TYPE_3__*) ; 
 int /*<<< orphan*/  wined3d_texture_cleanup_sync (struct wined3d_texture*) ; 
 struct wined3d_texture* wined3d_texture_init (struct wined3d_texture*,int /*<<< orphan*/ *,int,int,struct wined3d_resource_desc const*,int /*<<< orphan*/ ,struct wined3d_device*,void*,struct wined3d_parent_ops const*,int /*<<< orphan*/ *) ; 
 scalar_t__ wined3d_texture_use_pbo (struct wined3d_texture*,struct wined3d_gl_info const*) ; 

__attribute__((used)) static HRESULT volumetexture_init(struct wined3d_texture *texture, const struct wined3d_resource_desc *desc,
        UINT layer_count, UINT level_count, DWORD flags, struct wined3d_device *device, void *parent,
        const struct wined3d_parent_ops *parent_ops)
{
    struct wined3d_device_parent *device_parent = device->device_parent;
    const struct wined3d_gl_info *gl_info = &device->adapter->gl_info;
    unsigned int i;
    HRESULT hr;

    if (layer_count != 1)
    {
        ERR("Invalid layer count for volume texture.\n");
        return E_INVALIDARG;
    }

    /* TODO: It should only be possible to create textures for formats
     * that are reported as supported. */
    if (WINED3DFMT_UNKNOWN >= desc->format)
    {
        WARN("(%p) : Texture cannot be created with a format of WINED3DFMT_UNKNOWN.\n", texture);
        return WINED3DERR_INVALIDCALL;
    }

    if (!gl_info->supported[EXT_TEXTURE3D])
    {
        WARN("(%p) : Texture cannot be created - no volume texture support.\n", texture);
        return WINED3DERR_INVALIDCALL;
    }

    if (desc->usage & WINED3DUSAGE_DYNAMIC && (wined3d_resource_access_is_managed(desc->access)
            || desc->usage & WINED3DUSAGE_SCRATCH))
    {
        WARN("Attempted to create a DYNAMIC texture with access %s.\n",
                wined3d_debug_resource_access(desc->access));
        return WINED3DERR_INVALIDCALL;
    }

    if (!gl_info->supported[ARB_TEXTURE_NON_POWER_OF_TWO])
    {
        if (!is_power_of_two(desc->width) || !is_power_of_two(desc->height) || !is_power_of_two(desc->depth))
        {
            if (desc->usage & WINED3DUSAGE_SCRATCH)
            {
                WARN("Creating a scratch NPOT volume texture despite lack of HW support.\n");
            }
            else
            {
                WARN("Attempted to create a NPOT volume texture (%u, %u, %u) without GL support.\n",
                        desc->width, desc->height, desc->depth);
                return WINED3DERR_INVALIDCALL;
            }
        }
    }

    if (FAILED(hr = wined3d_texture_init(texture, &texture3d_ops, 1, level_count, desc,
            flags, device, parent, parent_ops, &texture_resource_ops)))
    {
        WARN("Failed to initialize texture, returning %#x.\n", hr);
        return hr;
    }

    texture->pow2_matrix[0] = 1.0f;
    texture->pow2_matrix[5] = 1.0f;
    texture->pow2_matrix[10] = 1.0f;
    texture->pow2_matrix[15] = 1.0f;
    texture->target = GL_TEXTURE_3D;

    if (wined3d_texture_use_pbo(texture, gl_info))
    {
        wined3d_resource_free_sysmem(&texture->resource);
        texture->resource.map_binding = WINED3D_LOCATION_BUFFER;
    }

    /* Generate all the sub resources. */
    for (i = 0; i < texture->level_count; ++i)
    {
        struct wined3d_texture_sub_resource *sub_resource;

        sub_resource = &texture->sub_resources[i];
        sub_resource->locations = WINED3D_LOCATION_DISCARDED;

        if (FAILED(hr = device_parent->ops->volume_created(device_parent,
                texture, i, &sub_resource->parent, &sub_resource->parent_ops)))
        {
            WARN("Failed to create volume parent, hr %#x.\n", hr);
            sub_resource->parent = NULL;
            wined3d_texture_cleanup_sync(texture);
            return hr;
        }

        TRACE("parent %p, parent_ops %p.\n", parent, parent_ops);

        TRACE("Created volume level %u.\n", i);
    }

    return WINED3D_OK;
}