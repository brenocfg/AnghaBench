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
struct TYPE_2__ {int /*<<< orphan*/ * lpVtbl; } ;
struct d3drm_wrap {int ref; int /*<<< orphan*/  obj; TYPE_1__ IDirect3DRMWrap_iface; } ;
typedef  int /*<<< orphan*/  IDirect3DRM ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,struct d3drm_wrap**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3drm_object_init (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  d3drm_wrap_vtbl ; 
 struct d3drm_wrap* heap_alloc_zero (int) ; 

HRESULT d3drm_wrap_create(struct d3drm_wrap **wrap, IDirect3DRM *d3drm)
{
    static const char classname[] = "";
    struct d3drm_wrap *object;

    TRACE("wrap %p, d3drm %p.\n", wrap, d3drm);

    if (!(object = heap_alloc_zero(sizeof(*object))))
        return E_OUTOFMEMORY;

    object->IDirect3DRMWrap_iface.lpVtbl = &d3drm_wrap_vtbl;
    object->ref = 1;

    d3drm_object_init(&object->obj, classname);

    *wrap = object;

    return S_OK;
}