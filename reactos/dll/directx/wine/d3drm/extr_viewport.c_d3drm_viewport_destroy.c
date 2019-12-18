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
struct d3drm_viewport {int /*<<< orphan*/  d3drm; int /*<<< orphan*/  camera; int /*<<< orphan*/  material; scalar_t__ d3d_viewport; int /*<<< orphan*/  obj; int /*<<< orphan*/  IDirect3DRMViewport_iface; } ;
typedef  int /*<<< orphan*/  IDirect3DRMObject ;

/* Variables and functions */
 int /*<<< orphan*/  IDirect3DMaterial_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DRMFrame_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DRM_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DViewport_Release (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,struct d3drm_viewport*) ; 
 int /*<<< orphan*/  d3drm_object_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (struct d3drm_viewport*) ; 

__attribute__((used)) static void d3drm_viewport_destroy(struct d3drm_viewport *viewport)
{
    TRACE("viewport %p releasing attached interfaces.\n", viewport);

    d3drm_object_cleanup((IDirect3DRMObject *)&viewport->IDirect3DRMViewport_iface, &viewport->obj);

    if (viewport->d3d_viewport)
    {
        IDirect3DViewport_Release(viewport->d3d_viewport);
        IDirect3DMaterial_Release(viewport->material);
        IDirect3DRMFrame_Release(viewport->camera);
        IDirect3DRM_Release(viewport->d3drm);
    }

    heap_free(viewport);
}