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
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct d3drm_device {int /*<<< orphan*/  obj; int /*<<< orphan*/ * d3drm; TYPE_3__ IDirect3DRMWinDevice_iface; TYPE_2__ IDirect3DRMDevice3_iface; TYPE_1__ IDirect3DRMDevice2_iface; TYPE_4__ IDirect3DRMDevice_iface; } ;
typedef  int /*<<< orphan*/  IDirect3DRM ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  D3DRM_OK ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  TRACE (char*,struct d3drm_device**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3drm_device1_vtbl ; 
 int /*<<< orphan*/  d3drm_device2_vtbl ; 
 int /*<<< orphan*/  d3drm_device3_vtbl ; 
 int /*<<< orphan*/  d3drm_device_win_vtbl ; 
 int /*<<< orphan*/  d3drm_object_init (int /*<<< orphan*/ *,char const*) ; 
 struct d3drm_device* heap_alloc_zero (int) ; 

HRESULT d3drm_device_create(struct d3drm_device **device, IDirect3DRM *d3drm)
{
    static const char classname[] = "Device";
    struct d3drm_device *object;

    TRACE("device %p, d3drm %p.\n", device, d3drm);

    if (!(object = heap_alloc_zero(sizeof(*object))))
        return E_OUTOFMEMORY;

    object->IDirect3DRMDevice_iface.lpVtbl = &d3drm_device1_vtbl;
    object->IDirect3DRMDevice2_iface.lpVtbl = &d3drm_device2_vtbl;
    object->IDirect3DRMDevice3_iface.lpVtbl = &d3drm_device3_vtbl;
    object->IDirect3DRMWinDevice_iface.lpVtbl = &d3drm_device_win_vtbl;
    object->d3drm = d3drm;
    d3drm_object_init(&object->obj, classname);

    *device = object;

    return D3DRM_OK;
}