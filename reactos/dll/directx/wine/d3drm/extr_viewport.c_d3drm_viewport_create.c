#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_3__ {int /*<<< orphan*/ * lpVtbl; } ;
struct d3drm_viewport {int /*<<< orphan*/  obj; int /*<<< orphan*/ * d3drm; TYPE_2__ IDirect3DRMViewport2_iface; TYPE_1__ IDirect3DRMViewport_iface; } ;
typedef  int /*<<< orphan*/  IDirect3DRM ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,struct d3drm_viewport**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3drm_object_init (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  d3drm_viewport1_vtbl ; 
 int /*<<< orphan*/  d3drm_viewport2_vtbl ; 
 struct d3drm_viewport* heap_alloc_zero (int) ; 

HRESULT d3drm_viewport_create(struct d3drm_viewport **viewport, IDirect3DRM *d3drm)
{
    static const char classname[] = "Viewport";
    struct d3drm_viewport *object;

    TRACE("viewport %p, d3drm %p.\n", viewport, d3drm);

    if (!(object = heap_alloc_zero(sizeof(*object))))
        return E_OUTOFMEMORY;

    object->IDirect3DRMViewport_iface.lpVtbl = &d3drm_viewport1_vtbl;
    object->IDirect3DRMViewport2_iface.lpVtbl = &d3drm_viewport2_vtbl;
    object->d3drm = d3drm;
    d3drm_object_init(&object->obj, classname);

    *viewport = object;

    return S_OK;
}