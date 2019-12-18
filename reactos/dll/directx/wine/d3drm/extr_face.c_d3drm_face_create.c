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
struct d3drm_face {int ref; int /*<<< orphan*/  obj; TYPE_2__ IDirect3DRMFace2_iface; TYPE_1__ IDirect3DRMFace_iface; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,struct d3drm_face**) ; 
 int /*<<< orphan*/  d3drm_face1_vtbl ; 
 int /*<<< orphan*/  d3drm_face2_vtbl ; 
 int /*<<< orphan*/  d3drm_object_init (int /*<<< orphan*/ *,char const*) ; 
 struct d3drm_face* heap_alloc_zero (int) ; 

HRESULT d3drm_face_create(struct d3drm_face **face)
{
    static const char classname[] = "Face";
    struct d3drm_face *object;

    TRACE("face %p.\n", face);

    if (!(object = heap_alloc_zero(sizeof(*object))))
        return E_OUTOFMEMORY;

    object->IDirect3DRMFace_iface.lpVtbl = &d3drm_face1_vtbl;
    object->IDirect3DRMFace2_iface.lpVtbl = &d3drm_face2_vtbl;
    object->ref = 1;

    d3drm_object_init(&object->obj, classname);

    *face = object;

    return S_OK;
}