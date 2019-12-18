#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_22__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_21__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_20__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_19__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_18__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_17__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_16__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_15__ {int /*<<< orphan*/ * lpVtbl; } ;
struct ddraw {int numIfaces; int ref7; int /*<<< orphan*/  surface_list; void* wined3d; int /*<<< orphan*/  wined3d_device; TYPE_12__ device_parent; int /*<<< orphan*/  flags; TYPE_8__ IDirect3D7_iface; TYPE_7__ IDirect3D3_iface; TYPE_6__ IDirect3D2_iface; TYPE_5__ IDirect3D_iface; TYPE_4__ IDirectDraw4_iface; TYPE_3__ IDirectDraw2_iface; TYPE_2__ IDirectDraw_iface; TYPE_1__ IDirectDraw7_iface; } ;
typedef  enum wined3d_device_type { ____Placeholder_wined3d_device_type } wined3d_device_type ;
struct TYPE_23__ {int caps; } ;
struct TYPE_13__ {TYPE_9__ ddraw_caps; } ;
typedef  TYPE_10__ WINED3DCAPS ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DDRAW_NO3D ; 
 int /*<<< orphan*/  DDRAW_STRIDE_ALIGNMENT ; 
 int /*<<< orphan*/  DDRAW_WINED3D_FLAGS ; 
 int /*<<< orphan*/  DD_OK ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  WINED3DADAPTER_DEFAULT ; 
 int /*<<< orphan*/  WINED3D_NO3D ; 
 int WINEDDCAPS_3D ; 
 int /*<<< orphan*/  d3d1_vtbl ; 
 int /*<<< orphan*/  d3d2_vtbl ; 
 int /*<<< orphan*/  d3d3_vtbl ; 
 int /*<<< orphan*/  d3d7_vtbl ; 
 int /*<<< orphan*/  ddraw1_vtbl ; 
 int /*<<< orphan*/  ddraw2_vtbl ; 
 int /*<<< orphan*/  ddraw4_vtbl ; 
 int /*<<< orphan*/  ddraw7_vtbl ; 
 int /*<<< orphan*/  ddraw_wined3d_device_parent_ops ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 void* wined3d_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_decref (void*) ; 
 int /*<<< orphan*/  wined3d_device_create (void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_12__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wined3d_get_device_caps (void*,int /*<<< orphan*/ ,int,TYPE_10__*) ; 

HRESULT ddraw_init(struct ddraw *ddraw, DWORD flags, enum wined3d_device_type device_type)
{
    WINED3DCAPS caps;
    HRESULT hr;

    ddraw->IDirectDraw7_iface.lpVtbl = &ddraw7_vtbl;
    ddraw->IDirectDraw_iface.lpVtbl = &ddraw1_vtbl;
    ddraw->IDirectDraw2_iface.lpVtbl = &ddraw2_vtbl;
    ddraw->IDirectDraw4_iface.lpVtbl = &ddraw4_vtbl;
    ddraw->IDirect3D_iface.lpVtbl = &d3d1_vtbl;
    ddraw->IDirect3D2_iface.lpVtbl = &d3d2_vtbl;
    ddraw->IDirect3D3_iface.lpVtbl = &d3d3_vtbl;
    ddraw->IDirect3D7_iface.lpVtbl = &d3d7_vtbl;
    ddraw->device_parent.ops = &ddraw_wined3d_device_parent_ops;
    ddraw->numIfaces = 1;
    ddraw->ref7 = 1;

    flags |= DDRAW_WINED3D_FLAGS;
    if (!(ddraw->wined3d = wined3d_create(flags)))
    {
        flags |= WINED3D_NO3D;
        if (!(ddraw->wined3d = wined3d_create(flags)))
        {
            WARN("Failed to create a wined3d object.\n");
            return E_FAIL;
        }
    }

    if (FAILED(hr = wined3d_get_device_caps(ddraw->wined3d, WINED3DADAPTER_DEFAULT, device_type, &caps)))
    {
        ERR("Failed to get device caps, hr %#x.\n", hr);
        wined3d_decref(ddraw->wined3d);
        return E_FAIL;
    }

    if (!(caps.ddraw_caps.caps & WINEDDCAPS_3D))
    {
        WARN("Created a wined3d object without 3D support.\n");
        ddraw->flags |= DDRAW_NO3D;
    }

    if (FAILED(hr = wined3d_device_create(ddraw->wined3d, WINED3DADAPTER_DEFAULT, device_type,
            NULL, 0, DDRAW_STRIDE_ALIGNMENT, &ddraw->device_parent, &ddraw->wined3d_device)))
    {
        WARN("Failed to create a wined3d device, hr %#x.\n", hr);
        wined3d_decref(ddraw->wined3d);
        return hr;
    }

    list_init(&ddraw->surface_list);

    return DD_OK;
}