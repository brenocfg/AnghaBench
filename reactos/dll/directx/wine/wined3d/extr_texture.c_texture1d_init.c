#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct wined3d_surface* surface; } ;
struct wined3d_texture_sub_resource {int /*<<< orphan*/ * parent; int /*<<< orphan*/  parent_ops; TYPE_2__ u; int /*<<< orphan*/  locations; } ;
struct TYPE_8__ {int /*<<< orphan*/  map_binding; } ;
struct wined3d_texture {float* pow2_matrix; unsigned int level_count; unsigned int layer_count; struct wined3d_texture_sub_resource* sub_resources; TYPE_4__ resource; int /*<<< orphan*/  target; } ;
struct wined3d_surface {unsigned int texture_level; unsigned int texture_layer; int /*<<< orphan*/  renderbuffers; struct wined3d_texture* container; } ;
struct wined3d_resource_desc {scalar_t__ format; int usage; int /*<<< orphan*/  depth; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  access; } ;
struct wined3d_parent_ops {int dummy; } ;
struct wined3d_gl_info {int /*<<< orphan*/ * supported; } ;
struct wined3d_device_parent {TYPE_3__* ops; } ;
struct wined3d_device {TYPE_1__* adapter; struct wined3d_device_parent* device_parent; } ;
typedef  int UINT ;
struct TYPE_7__ {struct wined3d_texture* (* surface_created ) (struct wined3d_device_parent*,struct wined3d_texture*,unsigned int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {struct wined3d_gl_info gl_info; } ;
typedef  int SIZE_T ;
typedef  struct wined3d_texture* HRESULT ;

/* Variables and functions */
 size_t ARB_TEXTURE_NON_POWER_OF_TWO ; 
 size_t EXT_TEXTURE_ARRAY ; 
 struct wined3d_texture* E_OUTOFMEMORY ; 
 scalar_t__ FAILED (struct wined3d_texture*) ; 
 int /*<<< orphan*/  GL_TEXTURE_1D ; 
 int /*<<< orphan*/  GL_TEXTURE_1D_ARRAY ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 struct wined3d_texture* WINED3DERR_INVALIDCALL ; 
 scalar_t__ WINED3DFMT_UNKNOWN ; 
 int WINED3DUSAGE_DYNAMIC ; 
 int WINED3DUSAGE_LEGACY_CUBEMAP ; 
 int WINED3DUSAGE_QUERY_GENMIPMAP ; 
 int WINED3DUSAGE_SCRATCH ; 
 int /*<<< orphan*/  WINED3D_LOCATION_BUFFER ; 
 int /*<<< orphan*/  WINED3D_LOCATION_DISCARDED ; 
 struct wined3d_texture* WINED3D_OK ; 
 struct wined3d_surface* heap_calloc (int,int) ; 
 int /*<<< orphan*/  is_power_of_two (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 struct wined3d_texture* stub1 (struct wined3d_device_parent*,struct wined3d_texture*,unsigned int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  texture1d_ops ; 
 int /*<<< orphan*/  texture_resource_ops ; 
 struct wined3d_texture* wined3d_debug_resource_access (int /*<<< orphan*/ ) ; 
 scalar_t__ wined3d_resource_access_is_managed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_resource_free_sysmem (TYPE_4__*) ; 
 int /*<<< orphan*/  wined3d_texture_cleanup_sync (struct wined3d_texture*) ; 
 struct wined3d_texture* wined3d_texture_init (struct wined3d_texture*,int /*<<< orphan*/ *,int,int,struct wined3d_resource_desc const*,int /*<<< orphan*/ ,struct wined3d_device*,void*,struct wined3d_parent_ops const*,int /*<<< orphan*/ *) ; 
 scalar_t__ wined3d_texture_use_pbo (struct wined3d_texture*,struct wined3d_gl_info const*) ; 

__attribute__((used)) static HRESULT texture1d_init(struct wined3d_texture *texture, const struct wined3d_resource_desc *desc,
        UINT layer_count, UINT level_count, struct wined3d_device *device, void *parent,
        const struct wined3d_parent_ops *parent_ops)
{
    struct wined3d_device_parent *device_parent = device->device_parent;
    const struct wined3d_gl_info *gl_info = &device->adapter->gl_info;
    struct wined3d_surface *surfaces;
    unsigned int i, j;
    HRESULT hr;

    if (layer_count > 1 && !gl_info->supported[EXT_TEXTURE_ARRAY])
    {
        WARN("OpenGL implementation does not support array textures.\n");
        return WINED3DERR_INVALIDCALL;
    }

    /* TODO: It should only be possible to create textures for formats
     * that are reported as supported. */
    if (WINED3DFMT_UNKNOWN >= desc->format)
    {
        WARN("(%p) : Texture cannot be created with a format of WINED3DFMT_UNKNOWN.\n", texture);
        return WINED3DERR_INVALIDCALL;
    }

    if (desc->usage & WINED3DUSAGE_LEGACY_CUBEMAP)
    {
        WARN("1d textures can not be used for cube mapping, returning D3DERR_INVALIDCALL.\n");
        return WINED3DERR_INVALIDCALL;
    }

    if ((desc->usage & WINED3DUSAGE_DYNAMIC && wined3d_resource_access_is_managed(desc->access))
            || (desc->usage & WINED3DUSAGE_SCRATCH))
    {
        WARN("Attempted to create a DYNAMIC texture in pool %s.\n", wined3d_debug_resource_access(desc->access));
        return WINED3DERR_INVALIDCALL;
    }

    if (!gl_info->supported[ARB_TEXTURE_NON_POWER_OF_TWO] && !is_power_of_two(desc->width))
    {
        if (desc->usage & WINED3DUSAGE_SCRATCH)
        {
            WARN("Creating a scratch NPOT 1d texture despite lack of HW support.\n");
        }
        else
        {
            WARN("Attempted to create a NPOT 1d texture (%u, %u, %u) without GL support.\n",
                    desc->width, desc->height, desc->depth);
            return WINED3DERR_INVALIDCALL;
        }
    }

    if (desc->usage & WINED3DUSAGE_QUERY_GENMIPMAP)
    {
        if (level_count != 1)
        {
            WARN("WINED3DUSAGE_QUERY_GENMIPMAP is set, and level count != 1, returning WINED3DERR_INVALIDCALL.\n");
            return WINED3DERR_INVALIDCALL;
        }
    }

    if (FAILED(hr = wined3d_texture_init(texture, &texture1d_ops, layer_count, level_count, desc,
            0, device, parent, parent_ops, &texture_resource_ops)))
    {
        WARN("Failed to initialize texture, returning %#x.\n", hr);
        return hr;
    }

    texture->pow2_matrix[0] = 1.0f;
    texture->pow2_matrix[5] = 1.0f;
    texture->pow2_matrix[10] = 1.0f;
    texture->pow2_matrix[15] = 1.0f;
    texture->target = (layer_count > 1) ? GL_TEXTURE_1D_ARRAY : GL_TEXTURE_1D;

    if (wined3d_texture_use_pbo(texture, gl_info))
    {
        wined3d_resource_free_sysmem(&texture->resource);
        texture->resource.map_binding = WINED3D_LOCATION_BUFFER;
    }

    if (level_count > ~(SIZE_T)0 / layer_count
            || !(surfaces = heap_calloc(level_count * layer_count, sizeof(*surfaces))))
    {
        wined3d_texture_cleanup_sync(texture);
        return E_OUTOFMEMORY;
    }

    /* Generate all the surfaces. */
    for (i = 0; i < texture->level_count; ++i)
    {
        for (j = 0; j < texture->layer_count; ++j)
        {
            struct wined3d_texture_sub_resource *sub_resource;
            unsigned int idx = j * texture->level_count + i;
            struct wined3d_surface *surface;

            surface = &surfaces[idx];
            surface->container = texture;
            surface->texture_level = i;
            surface->texture_layer = j;
            list_init(&surface->renderbuffers);

            sub_resource = &texture->sub_resources[idx];
            sub_resource->locations = WINED3D_LOCATION_DISCARDED;
            sub_resource->u.surface = surface;

            if (FAILED(hr = device_parent->ops->surface_created(device_parent,
                    texture, idx, &sub_resource->parent, &sub_resource->parent_ops)))
            {
                WARN("Failed to create texture1d parent, hr %#x.\n", hr);
                sub_resource->parent = NULL;
                wined3d_texture_cleanup_sync(texture);
                return hr;
            }

            TRACE("parent %p, parent_ops %p.\n", parent, parent_ops);

            TRACE("Created 1d texture surface level %u, layer %u @ %p.\n", i, j, surface);
        }
    }

    return WINED3D_OK;
}