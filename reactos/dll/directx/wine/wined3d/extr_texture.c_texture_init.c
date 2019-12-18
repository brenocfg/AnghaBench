#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {struct wined3d_surface* surface; } ;
struct wined3d_texture_sub_resource {int /*<<< orphan*/  parent_ops; int /*<<< orphan*/ * parent; TYPE_3__ u; int /*<<< orphan*/  locations; } ;
struct TYPE_14__ {scalar_t__ gl_type; int usage; int /*<<< orphan*/  map_binding; } ;
struct wined3d_texture {int flags; int pow2_width; int pow2_height; float* pow2_matrix; unsigned int level_count; unsigned int layer_count; TYPE_4__ resource; struct wined3d_texture_sub_resource* sub_resources; TYPE_2__* overlay_info; int /*<<< orphan*/  target; } ;
struct wined3d_surface {unsigned int texture_level; unsigned int texture_layer; int /*<<< orphan*/  dc; int /*<<< orphan*/  renderbuffers; struct wined3d_texture* container; } ;
struct wined3d_resource_desc {int usage; int access; int width; int height; scalar_t__ multisample_type; int /*<<< orphan*/  format; } ;
struct wined3d_parent_ops {int dummy; } ;
struct TYPE_11__ {int texture_size; } ;
struct wined3d_gl_info {scalar_t__* supported; TYPE_1__ limits; } ;
struct wined3d_format {int* flags; } ;
struct wined3d_device_parent {TYPE_5__* ops; } ;
struct wined3d_device {TYPE_9__* cs; TYPE_6__* wined3d; TYPE_8__* adapter; struct wined3d_device_parent* device_parent; } ;
typedef  int UINT ;
struct TYPE_19__ {TYPE_7__* ops; } ;
struct TYPE_18__ {struct wined3d_gl_info gl_info; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* finish ) (TYPE_9__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {int flags; } ;
struct TYPE_15__ {struct wined3d_texture* (* surface_created ) (struct wined3d_device_parent*,struct wined3d_texture*,unsigned int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  overlays; int /*<<< orphan*/  entry; } ;
typedef  struct wined3d_texture* HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 size_t ARB_TEXTURE_MULTISAMPLE ; 
 size_t ARB_TEXTURE_NON_POWER_OF_TWO ; 
 size_t ARB_TEXTURE_RECTANGLE ; 
 size_t EXT_TEXTURE_ARRAY ; 
 struct wined3d_texture* E_OUTOFMEMORY ; 
 scalar_t__ FAILED (struct wined3d_texture*) ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_2D_ARRAY ; 
 int /*<<< orphan*/  GL_TEXTURE_2D_MULTISAMPLE ; 
 int /*<<< orphan*/  GL_TEXTURE_2D_MULTISAMPLE_ARRAY ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_ARB ; 
 int /*<<< orphan*/  GL_TEXTURE_RECTANGLE_ARB ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 struct wined3d_texture* WINED3DERR_INVALIDCALL ; 
 struct wined3d_texture* WINED3DERR_NOTAVAILABLE ; 
 int WINED3DFMT_FLAG_COMPRESSED ; 
 int WINED3DFMT_FLAG_HEIGHT_SCALE ; 
 int /*<<< orphan*/  WINED3DFMT_UNKNOWN ; 
 int WINED3DUSAGE_DEPTHSTENCIL ; 
 int WINED3DUSAGE_DYNAMIC ; 
 int WINED3DUSAGE_LEGACY_CUBEMAP ; 
 int WINED3DUSAGE_OVERLAY ; 
 int WINED3DUSAGE_OWNDC ; 
 int WINED3DUSAGE_RENDERTARGET ; 
 int WINED3DUSAGE_SCRATCH ; 
 int WINED3DUSAGE_TEXTURE ; 
 int /*<<< orphan*/  WINED3D_CS_QUEUE_DEFAULT ; 
 size_t WINED3D_GL_NORMALIZED_TEXRECT ; 
 size_t WINED3D_GL_RES_TYPE_TEX_2D ; 
 scalar_t__ WINED3D_GL_RES_TYPE_TEX_RECT ; 
 int /*<<< orphan*/  WINED3D_LOCATION_BUFFER ; 
 int /*<<< orphan*/  WINED3D_LOCATION_DISCARDED ; 
 int /*<<< orphan*/  WINED3D_LOCATION_SYSMEM ; 
 int WINED3D_NO3D ; 
 struct wined3d_texture* WINED3D_OK ; 
 int WINED3D_RESOURCE_ACCESS_CPU ; 
 int WINED3D_RESOURCE_ACCESS_GPU ; 
 int WINED3D_TEXTURE_COND_NP2 ; 
 int WINED3D_TEXTURE_COND_NP2_EMULATED ; 
 int WINED3D_TEXTURE_CREATE_MAPPABLE ; 
 int WINED3D_TEXTURE_NORMALIZED_COORDS ; 
 int WINED3D_TEXTURE_POW2_MAT_IDENT ; 
 void* heap_calloc (unsigned int,int) ; 
 int /*<<< orphan*/  heap_free (struct wined3d_surface*) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 struct wined3d_texture* stub1 (struct wined3d_device_parent*,struct wined3d_texture*,unsigned int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  texture2d_create_dc ; 
 int /*<<< orphan*/  texture2d_ops ; 
 int /*<<< orphan*/  texture_resource_ops ; 
 int /*<<< orphan*/  wined3d_cs_init_object (TYPE_9__*,int /*<<< orphan*/ ,struct wined3d_surface*) ; 
 struct wined3d_format* wined3d_get_format (struct wined3d_gl_info const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wined3d_resource_access_is_managed (int) ; 
 int /*<<< orphan*/  wined3d_texture_cleanup_sync (struct wined3d_texture*) ; 
 struct wined3d_texture* wined3d_texture_init (struct wined3d_texture*,int /*<<< orphan*/ *,unsigned int,unsigned int,struct wined3d_resource_desc const*,int,struct wined3d_device*,void*,struct wined3d_parent_ops const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wined3d_texture_invalidate_location (struct wined3d_texture*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ wined3d_texture_use_pbo (struct wined3d_texture*,struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  wined3d_texture_validate_location (struct wined3d_texture*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT texture_init(struct wined3d_texture *texture, const struct wined3d_resource_desc *desc,
        unsigned int layer_count, unsigned int level_count, DWORD flags, struct wined3d_device *device,
        void *parent, const struct wined3d_parent_ops *parent_ops)
{
    struct wined3d_device_parent *device_parent = device->device_parent;
    const struct wined3d_gl_info *gl_info = &device->adapter->gl_info;
    struct wined3d_surface *surfaces;
    UINT pow2_width, pow2_height;
    unsigned int i, j, sub_count;
    HRESULT hr;

    if (!(desc->usage & WINED3DUSAGE_LEGACY_CUBEMAP) && layer_count > 1
            && !gl_info->supported[EXT_TEXTURE_ARRAY])
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

    if (desc->usage & WINED3DUSAGE_DYNAMIC && wined3d_resource_access_is_managed(desc->access))
        FIXME("Trying to create a managed texture with dynamic usage.\n");
    if (!(desc->usage & (WINED3DUSAGE_DYNAMIC | WINED3DUSAGE_RENDERTARGET | WINED3DUSAGE_DEPTHSTENCIL))
            && (flags & WINED3D_TEXTURE_CREATE_MAPPABLE))
        WARN("Creating a mappable texture that doesn't specify dynamic usage.\n");
    if (desc->usage & WINED3DUSAGE_RENDERTARGET && desc->access & WINED3D_RESOURCE_ACCESS_CPU)
        FIXME("Trying to create a CPU accessible render target.\n");

    pow2_width = desc->width;
    pow2_height = desc->height;
    if (((desc->width & (desc->width - 1)) || (desc->height & (desc->height - 1)))
            && !gl_info->supported[ARB_TEXTURE_NON_POWER_OF_TWO])
    {
        /* level_count == 0 returns an error as well. */
        if (level_count != 1 || layer_count != 1)
        {
            if (!(desc->usage & WINED3DUSAGE_SCRATCH))
            {
                WARN("Attempted to create a mipmapped/cube/array NPOT texture without unconditional NPOT support.\n");
                return WINED3DERR_INVALIDCALL;
            }

            WARN("Creating a scratch mipmapped/cube/array NPOT texture despite lack of HW support.\n");
        }
        texture->flags |= WINED3D_TEXTURE_COND_NP2;

        if (!gl_info->supported[ARB_TEXTURE_RECTANGLE] && !gl_info->supported[WINED3D_GL_NORMALIZED_TEXRECT])
        {
            const struct wined3d_format *format = wined3d_get_format(gl_info, desc->format, desc->usage);

            /* TODO: Add support for non-power-of-two compressed textures. */
            if (format->flags[WINED3D_GL_RES_TYPE_TEX_2D]
                    & (WINED3DFMT_FLAG_COMPRESSED | WINED3DFMT_FLAG_HEIGHT_SCALE))
            {
                FIXME("Compressed or height scaled non-power-of-two (%ux%u) textures are not supported.\n",
                        desc->width, desc->height);
                return WINED3DERR_NOTAVAILABLE;
            }

            /* Find the nearest pow2 match. */
            pow2_width = pow2_height = 1;
            while (pow2_width < desc->width)
                pow2_width <<= 1;
            while (pow2_height < desc->height)
                pow2_height <<= 1;
            texture->flags |= WINED3D_TEXTURE_COND_NP2_EMULATED;
        }
    }
    texture->pow2_width = pow2_width;
    texture->pow2_height = pow2_height;

    if ((pow2_width > gl_info->limits.texture_size || pow2_height > gl_info->limits.texture_size)
            && (desc->usage & WINED3DUSAGE_TEXTURE))
    {
        /* One of four options:
         * 1: Do the same as we do with NPOT and scale the texture. (Any
         *    texture ops would require the texture to be scaled which is
         *    potentially slow.)
         * 2: Set the texture to the maximum size (bad idea).
         * 3: WARN and return WINED3DERR_NOTAVAILABLE.
         * 4: Create the surface, but allow it to be used only for DirectDraw
         *    Blts. Some apps (e.g. Swat 3) create textures with a height of
         *    16 and a width > 3000 and blt 16x16 letter areas from them to
         *    the render target. */
        if (desc->access & WINED3D_RESOURCE_ACCESS_GPU)
        {
            WARN("Dimensions (%ux%u) exceed the maximum texture size.\n", pow2_width, pow2_height);
            return WINED3DERR_NOTAVAILABLE;
        }

        /* We should never use this surface in combination with OpenGL. */
        TRACE("Creating an oversized (%ux%u) surface.\n", pow2_width, pow2_height);
    }

    if (FAILED(hr = wined3d_texture_init(texture, &texture2d_ops, layer_count, level_count, desc,
            flags, device, parent, parent_ops, &texture_resource_ops)))
    {
        WARN("Failed to initialize texture, returning %#x.\n", hr);
        return hr;
    }

    /* Precalculated scaling for 'faked' non power of two texture coords. */
    if (texture->resource.gl_type == WINED3D_GL_RES_TYPE_TEX_RECT)
    {
        texture->pow2_matrix[0] = (float)desc->width;
        texture->pow2_matrix[5] = (float)desc->height;
        texture->flags &= ~(WINED3D_TEXTURE_POW2_MAT_IDENT | WINED3D_TEXTURE_NORMALIZED_COORDS);
        texture->target = GL_TEXTURE_RECTANGLE_ARB;
    }
    else
    {
        if (texture->flags & WINED3D_TEXTURE_COND_NP2_EMULATED)
        {
            texture->pow2_matrix[0] = (((float)desc->width) / ((float)pow2_width));
            texture->pow2_matrix[5] = (((float)desc->height) / ((float)pow2_height));
            texture->flags &= ~WINED3D_TEXTURE_POW2_MAT_IDENT;
        }
        else
        {
            texture->pow2_matrix[0] = 1.0f;
            texture->pow2_matrix[5] = 1.0f;
        }
        if (desc->usage & WINED3DUSAGE_LEGACY_CUBEMAP)
        {
            texture->target = GL_TEXTURE_CUBE_MAP_ARB;
        }
        else if (desc->multisample_type && gl_info->supported[ARB_TEXTURE_MULTISAMPLE])
        {
            if (layer_count > 1)
                texture->target = GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
            else
                texture->target = GL_TEXTURE_2D_MULTISAMPLE;
        }
        else
        {
            if (layer_count > 1)
                texture->target = GL_TEXTURE_2D_ARRAY;
            else
                texture->target = GL_TEXTURE_2D;
        }
    }
    texture->pow2_matrix[10] = 1.0f;
    texture->pow2_matrix[15] = 1.0f;
    TRACE("x scale %.8e, y scale %.8e.\n", texture->pow2_matrix[0], texture->pow2_matrix[5]);

    if (wined3d_texture_use_pbo(texture, gl_info))
        texture->resource.map_binding = WINED3D_LOCATION_BUFFER;

    sub_count = level_count * layer_count;
    if (sub_count / layer_count != level_count
            || !(surfaces = heap_calloc(sub_count, sizeof(*surfaces))))
    {
        wined3d_texture_cleanup_sync(texture);
        return E_OUTOFMEMORY;
    }

    if (desc->usage & WINED3DUSAGE_OVERLAY)
    {
        if (!(texture->overlay_info = heap_calloc(sub_count, sizeof(*texture->overlay_info))))
        {
            heap_free(surfaces);
            wined3d_texture_cleanup_sync(texture);
            return E_OUTOFMEMORY;
        }

        for (i = 0; i < sub_count; ++i)
        {
            list_init(&texture->overlay_info[i].entry);
            list_init(&texture->overlay_info[i].overlays);
        }
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
            if (!(texture->resource.usage & WINED3DUSAGE_DEPTHSTENCIL))
            {
                wined3d_texture_validate_location(texture, idx, WINED3D_LOCATION_SYSMEM);
                wined3d_texture_invalidate_location(texture, idx, ~WINED3D_LOCATION_SYSMEM);
            }

            if (FAILED(hr = device_parent->ops->surface_created(device_parent,
                    texture, idx, &sub_resource->parent, &sub_resource->parent_ops)))
            {
                WARN("Failed to create surface parent, hr %#x.\n", hr);
                sub_resource->parent = NULL;
                wined3d_texture_cleanup_sync(texture);
                return hr;
            }

            TRACE("parent %p, parent_ops %p.\n", sub_resource->parent, sub_resource->parent_ops);

            TRACE("Created surface level %u, layer %u @ %p.\n", i, j, surface);

            if ((desc->usage & WINED3DUSAGE_OWNDC) || (device->wined3d->flags & WINED3D_NO3D))
            {
                wined3d_cs_init_object(device->cs, texture2d_create_dc, surface);
                device->cs->ops->finish(device->cs, WINED3D_CS_QUEUE_DEFAULT);
                if (!surface->dc)
                {
                    wined3d_texture_cleanup_sync(texture);
                    return WINED3DERR_INVALIDCALL;
                }
            }
        }
    }

    return WINED3D_OK;
}