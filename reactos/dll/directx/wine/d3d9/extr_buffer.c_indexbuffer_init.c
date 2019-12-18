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
struct wined3d_buffer_desc {int usage; int access; scalar_t__ structure_byte_stride; scalar_t__ misc_flags; int /*<<< orphan*/  bind_flags; int /*<<< orphan*/  byte_width; } ;
struct TYPE_2__ {int /*<<< orphan*/ * lpVtbl; } ;
struct d3d9_indexbuffer {int /*<<< orphan*/ * parent_device; int /*<<< orphan*/  wined3d_buffer; int /*<<< orphan*/  resource; int /*<<< orphan*/  format; TYPE_1__ IDirect3DIndexBuffer9_iface; } ;
struct d3d9_device {int /*<<< orphan*/  IDirect3DDevice9Ex_iface; int /*<<< orphan*/  wined3d_device; } ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  scalar_t__ D3DPOOL ;
typedef  int /*<<< orphan*/  D3DFORMAT ;

/* Variables and functions */
 scalar_t__ D3DPOOL_SCRATCH ; 
 int /*<<< orphan*/  D3D_OK ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9Ex_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int WINED3DUSAGE_MASK ; 
 int WINED3DUSAGE_SCRATCH ; 
 int WINED3DUSAGE_STATICDECL ; 
 int /*<<< orphan*/  WINED3D_BIND_INDEX_BUFFER ; 
 int WINED3D_RESOURCE_ACCESS_MAP_R ; 
 int WINED3D_RESOURCE_ACCESS_MAP_W ; 
 int /*<<< orphan*/  d3d9_indexbuffer_vtbl ; 
 int /*<<< orphan*/  d3d9_indexbuffer_wined3d_parent_ops ; 
 int /*<<< orphan*/  d3d9_resource_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wined3d_buffer_create (int /*<<< orphan*/ ,struct wined3d_buffer_desc*,int /*<<< orphan*/ *,struct d3d9_indexbuffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wined3d_mutex_lock () ; 
 int /*<<< orphan*/  wined3d_mutex_unlock () ; 
 int wined3daccess_from_d3dpool (scalar_t__,int) ; 
 int /*<<< orphan*/  wined3dformat_from_d3dformat (int /*<<< orphan*/ ) ; 

HRESULT indexbuffer_init(struct d3d9_indexbuffer *buffer, struct d3d9_device *device,
        UINT size, DWORD usage, D3DFORMAT format, D3DPOOL pool)
{
    struct wined3d_buffer_desc desc;
    HRESULT hr;

    desc.byte_width = size;
    desc.usage = (usage & WINED3DUSAGE_MASK) | WINED3DUSAGE_STATICDECL;
    if (pool == D3DPOOL_SCRATCH)
        desc.usage |= WINED3DUSAGE_SCRATCH;
    desc.bind_flags = WINED3D_BIND_INDEX_BUFFER;
    desc.access = wined3daccess_from_d3dpool(pool, usage)
            | WINED3D_RESOURCE_ACCESS_MAP_R | WINED3D_RESOURCE_ACCESS_MAP_W;
    desc.misc_flags = 0;
    desc.structure_byte_stride = 0;

    buffer->IDirect3DIndexBuffer9_iface.lpVtbl = &d3d9_indexbuffer_vtbl;
    buffer->format = wined3dformat_from_d3dformat(format);
    d3d9_resource_init(&buffer->resource);

    wined3d_mutex_lock();
    hr = wined3d_buffer_create(device->wined3d_device, &desc, NULL, buffer,
            &d3d9_indexbuffer_wined3d_parent_ops, &buffer->wined3d_buffer);
    wined3d_mutex_unlock();
    if (FAILED(hr))
    {
        WARN("Failed to create wined3d buffer, hr %#x.\n", hr);
        return hr;
    }

    buffer->parent_device = &device->IDirect3DDevice9Ex_iface;
    IDirect3DDevice9Ex_AddRef(buffer->parent_device);

    return D3D_OK;
}