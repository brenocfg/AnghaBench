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
struct wined3d_resource_desc {int usage; int access; int width; int height; int depth; int /*<<< orphan*/  format; scalar_t__ size; scalar_t__ multisample_quality; int /*<<< orphan*/  multisample_type; int /*<<< orphan*/  resource_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  const* lpVtbl; } ;
struct d3d9_texture {int usage; int /*<<< orphan*/ * parent_device; int /*<<< orphan*/  wined3d_texture; int /*<<< orphan*/  autogen_filter_type; int /*<<< orphan*/  rtv_list; int /*<<< orphan*/  resource; TYPE_1__ IDirect3DBaseTexture9_iface; } ;
struct d3d9_device {int /*<<< orphan*/  IDirect3DDevice9Ex_iface; int /*<<< orphan*/  wined3d_device; } ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  IDirect3DBaseTexture9Vtbl ;
typedef  int HRESULT ;
typedef  int DWORD ;
typedef  scalar_t__ D3DPOOL ;
typedef  int /*<<< orphan*/  D3DFORMAT ;

/* Variables and functions */
 int D3DERR_INVALIDCALL ; 
 scalar_t__ D3DPOOL_DEFAULT ; 
 scalar_t__ D3DPOOL_SCRATCH ; 
 scalar_t__ D3DPOOL_SYSTEMMEM ; 
 int /*<<< orphan*/  D3DTEXF_LINEAR ; 
 int /*<<< orphan*/  D3DTEXF_NONE ; 
 int D3DUSAGE_AUTOGENMIPMAP ; 
 int D3DUSAGE_DYNAMIC ; 
 int D3D_OK ; 
 scalar_t__ FAILED (int) ; 
 int /*<<< orphan*/  IDirect3DDevice9Ex_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int WINED3DUSAGE_LEGACY_CUBEMAP ; 
 int WINED3DUSAGE_SCRATCH ; 
 int WINED3DUSAGE_TEXTURE ; 
 int /*<<< orphan*/  WINED3D_MULTISAMPLE_NONE ; 
 int WINED3D_RESOURCE_ACCESS_MAP_R ; 
 int WINED3D_RESOURCE_ACCESS_MAP_W ; 
 int /*<<< orphan*/  WINED3D_RTYPE_TEXTURE_2D ; 
 int WINED3D_TEXTURE_CREATE_GENERATE_MIPMAPS ; 
 int WINED3D_TEXTURE_CREATE_GET_DC ; 
 int WINED3D_TEXTURE_CREATE_MAPPABLE ; 
 int /*<<< orphan*/  d3d9_resource_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3d9_texture_cube_vtbl ; 
 int /*<<< orphan*/  d3d9_texture_wined3d_parent_ops ; 
 scalar_t__ is_gdi_compat_wined3dformat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int wined3d_log2i (int) ; 
 int /*<<< orphan*/  wined3d_mutex_lock () ; 
 int /*<<< orphan*/  wined3d_mutex_unlock () ; 
 int wined3d_texture_create (int /*<<< orphan*/ ,struct wined3d_resource_desc*,int,int,int,int /*<<< orphan*/ *,struct d3d9_texture*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int wined3daccess_from_d3dpool (scalar_t__,int) ; 
 int /*<<< orphan*/  wined3dformat_from_d3dformat (int /*<<< orphan*/ ) ; 
 int wined3dusage_from_d3dusage (int) ; 

HRESULT cubetexture_init(struct d3d9_texture *texture, struct d3d9_device *device,
        UINT edge_length, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool)
{
    struct wined3d_resource_desc desc;
    DWORD flags = 0;
    HRESULT hr;

    texture->IDirect3DBaseTexture9_iface.lpVtbl = (const IDirect3DBaseTexture9Vtbl *)&d3d9_texture_cube_vtbl;
    d3d9_resource_init(&texture->resource);
    list_init(&texture->rtv_list);
    texture->usage = usage;

    desc.resource_type = WINED3D_RTYPE_TEXTURE_2D;
    desc.format = wined3dformat_from_d3dformat(format);
    desc.multisample_type = WINED3D_MULTISAMPLE_NONE;
    desc.multisample_quality = 0;
    desc.usage = wined3dusage_from_d3dusage(usage);
    desc.usage |= WINED3DUSAGE_LEGACY_CUBEMAP | WINED3DUSAGE_TEXTURE;
    if (pool == D3DPOOL_SCRATCH)
        desc.usage |= WINED3DUSAGE_SCRATCH;
    desc.access = wined3daccess_from_d3dpool(pool, usage)
            | WINED3D_RESOURCE_ACCESS_MAP_R | WINED3D_RESOURCE_ACCESS_MAP_W;
    desc.width = edge_length;
    desc.height = edge_length;
    desc.depth = 1;
    desc.size = 0;

    if (pool != D3DPOOL_DEFAULT || (usage & D3DUSAGE_DYNAMIC))
        flags |= WINED3D_TEXTURE_CREATE_MAPPABLE;

    if (is_gdi_compat_wined3dformat(desc.format))
        flags |= WINED3D_TEXTURE_CREATE_GET_DC;

    if (usage & D3DUSAGE_AUTOGENMIPMAP)
    {
        if (pool == D3DPOOL_SYSTEMMEM)
        {
            WARN("D3DUSAGE_AUTOGENMIPMAP texture can't be in D3DPOOL_SYSTEMMEM, returning D3DERR_INVALIDCALL.\n");
            return D3DERR_INVALIDCALL;
        }
        if (levels && levels != 1)
        {
            WARN("D3DUSAGE_AUTOGENMIPMAP texture with %u levels, returning D3DERR_INVALIDCALL.\n", levels);
            return D3DERR_INVALIDCALL;
        }
        flags |= WINED3D_TEXTURE_CREATE_GENERATE_MIPMAPS;
        texture->autogen_filter_type = D3DTEXF_LINEAR;
        levels = 0;
    }
    else
    {
        texture->autogen_filter_type = D3DTEXF_NONE;
    }
    if (!levels)
        levels = wined3d_log2i(edge_length) + 1;

    wined3d_mutex_lock();
    hr = wined3d_texture_create(device->wined3d_device, &desc, 6, levels, flags,
            NULL, texture, &d3d9_texture_wined3d_parent_ops, &texture->wined3d_texture);
    wined3d_mutex_unlock();
    if (FAILED(hr))
    {
        WARN("Failed to create wined3d cube texture, hr %#x.\n", hr);
        return hr;
    }

    texture->parent_device = &device->IDirect3DDevice9Ex_iface;
    IDirect3DDevice9Ex_AddRef(texture->parent_device);

    return D3D_OK;
}