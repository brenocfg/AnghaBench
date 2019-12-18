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
struct wined3d_swapchain_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * lpVtbl; } ;
struct d3d8_swapchain {int refcount; int /*<<< orphan*/ * parent_device; int /*<<< orphan*/  wined3d_swapchain; TYPE_1__ IDirect3DSwapChain8_iface; } ;
struct d3d8_device {int /*<<< orphan*/  IDirect3DDevice8_iface; int /*<<< orphan*/  wined3d_device; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  D3D_OK ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice8_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d8_swapchain_vtbl ; 
 int /*<<< orphan*/  d3d8_swapchain_wined3d_parent_ops ; 
 int /*<<< orphan*/  wined3d_mutex_lock () ; 
 int /*<<< orphan*/  wined3d_mutex_unlock () ; 
 int /*<<< orphan*/  wined3d_swapchain_create (int /*<<< orphan*/ ,struct wined3d_swapchain_desc*,struct d3d8_swapchain*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT swapchain_init(struct d3d8_swapchain *swapchain, struct d3d8_device *device,
        struct wined3d_swapchain_desc *desc)
{
    HRESULT hr;

    swapchain->refcount = 1;
    swapchain->IDirect3DSwapChain8_iface.lpVtbl = &d3d8_swapchain_vtbl;

    wined3d_mutex_lock();
    hr = wined3d_swapchain_create(device->wined3d_device, desc, swapchain,
            &d3d8_swapchain_wined3d_parent_ops, &swapchain->wined3d_swapchain);
    wined3d_mutex_unlock();

    if (FAILED(hr))
    {
        WARN("Failed to create wined3d swapchain, hr %#x.\n", hr);
        return hr;
    }

    swapchain->parent_device = &device->IDirect3DDevice8_iface;
    IDirect3DDevice8_AddRef(swapchain->parent_device);

    return D3D_OK;
}