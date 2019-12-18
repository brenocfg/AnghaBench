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
struct wined3d_stateblock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * lpVtbl; } ;
struct d3d9_stateblock {int refcount; int /*<<< orphan*/ * parent_device; struct wined3d_stateblock* wined3d_stateblock; TYPE_1__ IDirect3DStateBlock9_iface; } ;
struct d3d9_device {int /*<<< orphan*/  IDirect3DDevice9Ex_iface; int /*<<< orphan*/  wined3d_device; } ;
typedef  enum wined3d_stateblock_type { ____Placeholder_wined3d_stateblock_type } wined3d_stateblock_type ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ D3DSTATEBLOCKTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  D3D_OK ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9Ex_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_stateblock_vtbl ; 
 int /*<<< orphan*/  wined3d_mutex_lock () ; 
 int /*<<< orphan*/  wined3d_mutex_unlock () ; 
 int /*<<< orphan*/  wined3d_stateblock_create (int /*<<< orphan*/ ,int,struct wined3d_stateblock**) ; 

HRESULT stateblock_init(struct d3d9_stateblock *stateblock, struct d3d9_device *device,
        D3DSTATEBLOCKTYPE type, struct wined3d_stateblock *wined3d_stateblock)
{
    HRESULT hr;

    stateblock->IDirect3DStateBlock9_iface.lpVtbl = &d3d9_stateblock_vtbl;
    stateblock->refcount = 1;

    if (wined3d_stateblock)
    {
        stateblock->wined3d_stateblock = wined3d_stateblock;
    }
    else
    {
        wined3d_mutex_lock();
        hr = wined3d_stateblock_create(device->wined3d_device,
                (enum wined3d_stateblock_type)type, &stateblock->wined3d_stateblock);
        wined3d_mutex_unlock();
        if (FAILED(hr))
        {
            WARN("Failed to create wined3d stateblock, hr %#x.\n", hr);
            return hr;
        }
    }

    stateblock->parent_device = &device->IDirect3DDevice9Ex_iface;
    IDirect3DDevice9Ex_AddRef(stateblock->parent_device);

    return D3D_OK;
}