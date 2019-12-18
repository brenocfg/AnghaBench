#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct d3drm_viewport {int /*<<< orphan*/  material; int /*<<< orphan*/  camera; } ;
typedef  int /*<<< orphan*/  mat ;
struct TYPE_5__ {int /*<<< orphan*/  diffuse; } ;
struct TYPE_6__ {int dwSize; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  IDirect3DRMFrame ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ D3DMATERIAL ;
typedef  int /*<<< orphan*/  D3DCOLOR ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DMaterial_SetMaterial (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  IDirect3DRMFrame_GetScene (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDirect3DRMFrame_GetSceneBackground (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DRMFrame_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3drm_normalize_d3d_color (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HRESULT d3drm_update_background_material(struct d3drm_viewport *viewport)
{
    IDirect3DRMFrame *root_frame;
    D3DCOLOR color;
    D3DMATERIAL mat;
    HRESULT hr;

    if (FAILED(hr = IDirect3DRMFrame_GetScene(viewport->camera, &root_frame)))
        return hr;
    color = IDirect3DRMFrame_GetSceneBackground(root_frame);
    IDirect3DRMFrame_Release(root_frame);

    memset(&mat, 0, sizeof(mat));
    mat.dwSize = sizeof(mat);
    d3drm_normalize_d3d_color(&mat.u.diffuse, color);

    return IDirect3DMaterial_SetMaterial(viewport->material, &mat);
}