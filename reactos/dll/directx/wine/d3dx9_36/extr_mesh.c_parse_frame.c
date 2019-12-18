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
struct mesh_container {int /*<<< orphan*/  mesh; int /*<<< orphan*/  num_materials; int /*<<< orphan*/  materials; int /*<<< orphan*/  adjacency; int /*<<< orphan*/  transform; int /*<<< orphan*/  entry; } ;
struct list {int dummy; } ;
struct IDirect3DDevice9 {int dummy; } ;
struct ID3DXFileData {TYPE_1__* lpVtbl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* GetType ) (struct ID3DXFileData*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* GetChild ) (struct ID3DXFileData*,scalar_t__,struct ID3DXFileData**) ;int /*<<< orphan*/  (* GetChildren ) (struct ID3DXFileData*,scalar_t__*) ;} ;
typedef  scalar_t__ SIZE_T ;
typedef  struct ID3DXFileData ID3DXFileData ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  D3DXMATRIX ;

/* Variables and functions */
 int /*<<< orphan*/  D3DXLoadSkinMeshFromXof (struct ID3DXFileData*,int,struct IDirect3DDevice9*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3DXMatrixMultiply (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 struct mesh_container* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IUnknown_Release (struct ID3DXFileData*) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PROVIDE_ADJACENCY ; 
 int PROVIDE_MATERIALS ; 
 int /*<<< orphan*/  TID_D3DRMFrame ; 
 int /*<<< orphan*/  TID_D3DRMFrameTransformMatrix ; 
 int /*<<< orphan*/  TID_D3DRMMesh ; 
 int /*<<< orphan*/  list_add_tail (struct list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_transform_matrix (struct ID3DXFileData*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ID3DXFileData*,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (struct ID3DXFileData*,scalar_t__,struct ID3DXFileData**) ; 
 int /*<<< orphan*/  stub3 (struct ID3DXFileData*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT parse_frame(struct ID3DXFileData *filedata, DWORD options, struct IDirect3DDevice9 *device,
        const D3DXMATRIX *parent_transform, struct list *container_list, DWORD provide_flags)
{
    HRESULT hr;
    D3DXMATRIX transform = *parent_transform;
    ID3DXFileData *child;
    GUID type;
    SIZE_T i, nb_children;

    hr = filedata->lpVtbl->GetChildren(filedata, &nb_children);
    if (FAILED(hr))
        return hr;

    for (i = 0; i < nb_children; i++)
    {
        hr = filedata->lpVtbl->GetChild(filedata, i, &child);
        if (FAILED(hr))
            return hr;
        hr = child->lpVtbl->GetType(child, &type);
        if (FAILED(hr))
            goto err;

        if (IsEqualGUID(&type, &TID_D3DRMMesh)) {
            struct mesh_container *container = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*container));
            if (!container)
            {
                hr = E_OUTOFMEMORY;
                goto err;
            }
            list_add_tail(container_list, &container->entry);
            container->transform = transform;

            hr = D3DXLoadSkinMeshFromXof(child, options, device,
                    (provide_flags & PROVIDE_ADJACENCY) ? &container->adjacency : NULL,
                    (provide_flags & PROVIDE_MATERIALS) ? &container->materials : NULL,
                    NULL, &container->num_materials, NULL, &container->mesh);
        } else if (IsEqualGUID(&type, &TID_D3DRMFrameTransformMatrix)) {
            D3DXMATRIX new_transform;
            hr = parse_transform_matrix(child, &new_transform);
            D3DXMatrixMultiply(&transform, &transform, &new_transform);
        } else if (IsEqualGUID(&type, &TID_D3DRMFrame)) {
            hr = parse_frame(child, options, device, &transform, container_list, provide_flags);
        }
        if (FAILED(hr))
            goto err;

        IUnknown_Release(child);
    }
    return D3D_OK;

err:
    IUnknown_Release(child);
    return hr;
}