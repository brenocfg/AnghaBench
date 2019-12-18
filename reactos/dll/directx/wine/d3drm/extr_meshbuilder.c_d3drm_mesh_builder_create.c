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
struct d3drm_mesh_builder {int ref; int /*<<< orphan*/  obj; int /*<<< orphan*/ * d3drm; TYPE_2__ IDirect3DRMMeshBuilder3_iface; TYPE_1__ IDirect3DRMMeshBuilder2_iface; } ;
typedef  int /*<<< orphan*/  IDirect3DRM ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IDirect3DRM_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,struct d3drm_mesh_builder**) ; 
 int /*<<< orphan*/  d3drm_mesh_builder2_vtbl ; 
 int /*<<< orphan*/  d3drm_mesh_builder3_vtbl ; 
 int /*<<< orphan*/  d3drm_object_init (int /*<<< orphan*/ *,char const*) ; 
 struct d3drm_mesh_builder* heap_alloc_zero (int) ; 

HRESULT d3drm_mesh_builder_create(struct d3drm_mesh_builder **mesh_builder, IDirect3DRM *d3drm)
{
    static const char classname[] = "Builder";
    struct d3drm_mesh_builder *object;

    TRACE("mesh_builder %p.\n", mesh_builder);

    if (!(object = heap_alloc_zero(sizeof(*object))))
        return E_OUTOFMEMORY;

    object->IDirect3DRMMeshBuilder2_iface.lpVtbl = &d3drm_mesh_builder2_vtbl;
    object->IDirect3DRMMeshBuilder3_iface.lpVtbl = &d3drm_mesh_builder3_vtbl;
    object->ref = 1;
    object->d3drm = d3drm;
    IDirect3DRM_AddRef(object->d3drm);

    d3drm_object_init(&object->obj, classname);

    *mesh_builder = object;

    return S_OK;
}