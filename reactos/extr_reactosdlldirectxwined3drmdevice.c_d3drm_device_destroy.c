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
struct d3drm_device {int /*<<< orphan*/  d3drm; scalar_t__ ddraw; int /*<<< orphan*/  clipper; scalar_t__ primary_surface; scalar_t__ render_target; scalar_t__ device; int /*<<< orphan*/  obj; int /*<<< orphan*/  IDirect3DRMDevice_iface; } ;
typedef  int /*<<< orphan*/  IDirect3DRMObject ;

/* Variables and functions */
 int /*<<< orphan*/  IDirect3DDevice_Release (scalar_t__) ; 
 int /*<<< orphan*/  IDirect3DRM_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectDrawClipper_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectDrawSurface_Release (scalar_t__) ; 
 int /*<<< orphan*/  IDirectDraw_Release (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  d3drm_object_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (struct d3drm_device*) ; 

void d3drm_device_destroy(struct d3drm_device *device)
{
    d3drm_object_cleanup((IDirect3DRMObject *)&device->IDirect3DRMDevice_iface, &device->obj);
    if (device->device)
    {
        TRACE("Releasing attached ddraw interfaces.\n");
        IDirect3DDevice_Release(device->device);
    }
    if (device->render_target)
        IDirectDrawSurface_Release(device->render_target);
    if (device->primary_surface)
    {
        TRACE("Releasing primary surface and attached clipper.\n");
        IDirectDrawSurface_Release(device->primary_surface);
        IDirectDrawClipper_Release(device->clipper);
    }
    if (device->ddraw)
    {
        IDirectDraw_Release(device->ddraw);
        IDirect3DRM_Release(device->d3drm);
    }
    heap_free(device);
}