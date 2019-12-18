#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wined3d_swapchain_desc {int dummy; } ;
struct d3d8_swapchain {int dummy; } ;
struct d3d8_device {int dummy; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,struct d3d8_swapchain*) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 struct d3d8_swapchain* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (struct d3d8_swapchain*) ; 
 int /*<<< orphan*/  swapchain_init (struct d3d8_swapchain*,struct d3d8_device*,struct wined3d_swapchain_desc*) ; 

HRESULT d3d8_swapchain_create(struct d3d8_device *device, struct wined3d_swapchain_desc *desc,
        struct d3d8_swapchain **swapchain)
{
    struct d3d8_swapchain *object;
    HRESULT hr;

    if (!(object = heap_alloc_zero(sizeof(*object))))
        return E_OUTOFMEMORY;

    if (FAILED(hr = swapchain_init(object, device, desc)))
    {
        WARN("Failed to initialize swapchain, hr %#x.\n", hr);
        heap_free(object);
        return hr;
    }

    TRACE("Created swapchain %p.\n", object);
    *swapchain = object;

    return D3D_OK;
}