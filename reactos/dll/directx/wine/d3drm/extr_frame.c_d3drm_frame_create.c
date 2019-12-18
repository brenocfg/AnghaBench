#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct d3drm_frame {int ref; int traversal_options; int /*<<< orphan*/ * d3drm; TYPE_3__ IDirect3DRMFrame3_iface; int /*<<< orphan*/  transform; int /*<<< orphan*/  obj; int /*<<< orphan*/  scenebackground; TYPE_2__ IDirect3DRMFrame2_iface; TYPE_1__ IDirect3DRMFrame_iface; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IDirect3DRMFrame3 ;
typedef  int /*<<< orphan*/  IDirect3DRM ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int D3DRMFRAME_PICKENABLE ; 
 int D3DRMFRAME_RENDERENABLE ; 
 int /*<<< orphan*/  D3DRM_OK ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DRMFrame3_AddChild (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  IDirect3DRMFrame_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDirect3DRMFrame_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DRM_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDirect3DRMFrame3 ; 
 int /*<<< orphan*/  TRACE (char*,struct d3drm_frame**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3drm_frame1_vtbl ; 
 int /*<<< orphan*/  d3drm_frame2_vtbl ; 
 int /*<<< orphan*/  d3drm_frame3_vtbl ; 
 int /*<<< orphan*/  d3drm_object_init (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  d3drm_set_color (int /*<<< orphan*/ *,float,float,float,float) ; 
 struct d3drm_frame* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (struct d3drm_frame*) ; 
 int /*<<< orphan*/  identity ; 

HRESULT d3drm_frame_create(struct d3drm_frame **frame, IUnknown *parent_frame, IDirect3DRM *d3drm)
{
    static const char classname[] = "Frame";
    struct d3drm_frame *object;
    HRESULT hr = D3DRM_OK;

    TRACE("frame %p, parent_frame %p, d3drm %p.\n", frame, parent_frame, d3drm);

    if (!(object = heap_alloc_zero(sizeof(*object))))
        return E_OUTOFMEMORY;

    object->IDirect3DRMFrame_iface.lpVtbl = &d3drm_frame1_vtbl;
    object->IDirect3DRMFrame2_iface.lpVtbl = &d3drm_frame2_vtbl;
    object->IDirect3DRMFrame3_iface.lpVtbl = &d3drm_frame3_vtbl;
    object->d3drm = d3drm;
    object->ref = 1;
    d3drm_set_color(&object->scenebackground, 0.0f, 0.0f, 0.0f, 1.0f);
    object->traversal_options = D3DRMFRAME_RENDERENABLE | D3DRMFRAME_PICKENABLE;

    d3drm_object_init(&object->obj, classname);

    object->transform = identity;

    if (parent_frame)
    {
        IDirect3DRMFrame3 *p;

        if (FAILED(hr = IDirect3DRMFrame_QueryInterface(parent_frame, &IID_IDirect3DRMFrame3, (void **)&p)))
        {
            heap_free(object);
            return hr;
        }
        IDirect3DRMFrame_Release(parent_frame);
        IDirect3DRMFrame3_AddChild(p, &object->IDirect3DRMFrame3_iface);
    }

    IDirect3DRM_AddRef(object->d3drm);

    *frame = object;

    return hr;
}