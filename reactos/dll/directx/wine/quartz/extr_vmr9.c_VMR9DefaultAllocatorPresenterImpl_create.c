#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct quartz_vmr {int /*<<< orphan*/  hD3d9; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int refCount; TYPE_3__ IVMRImagePresenter9_iface; int /*<<< orphan*/  reset; int /*<<< orphan*/ * SurfaceAllocatorNotify; int /*<<< orphan*/  ack; int /*<<< orphan*/ * hWndThread; scalar_t__ num_surfaces; int /*<<< orphan*/ * d3d9_vertex; scalar_t__ hMon; int /*<<< orphan*/ * d3d9_dev; int /*<<< orphan*/ * d3d9_surfaces; struct quartz_vmr* pVMR9; TYPE_1__ IVMRSurfaceAllocatorEx9_iface; int /*<<< orphan*/  d3d9_ptr; } ;
typedef  TYPE_2__ VMR9DefaultAllocatorPresenterImpl ;
typedef  TYPE_3__* LPVOID ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  D3DDISPLAYMODE ;

/* Variables and functions */
 TYPE_2__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  CoTaskMemFree (TYPE_2__*) ; 
 int /*<<< orphan*/  CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ D3DERR_INVALIDCALL ; 
 scalar_t__ D3DERR_NOTAVAILABLE ; 
 int /*<<< orphan*/  D3DFMT_X8R8G8B8 ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IDirect3D9_EnumAdapterModes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3D9_Release (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 scalar_t__ VFW_E_DDRAW_CAPS_NOT_SUITABLE ; 
 int /*<<< orphan*/  VMR9_ImagePresenter ; 
 int /*<<< orphan*/  VMR9_SurfaceAllocator ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  init_d3d9 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT VMR9DefaultAllocatorPresenterImpl_create(struct quartz_vmr *parent, LPVOID * ppv)
{
    HRESULT hr = S_OK;
    int i;
    VMR9DefaultAllocatorPresenterImpl* This;

    This = CoTaskMemAlloc(sizeof(VMR9DefaultAllocatorPresenterImpl));
    if (!This)
        return E_OUTOFMEMORY;

    This->d3d9_ptr = init_d3d9(parent->hD3d9);
    if (!This->d3d9_ptr)
    {
        WARN("Could not initialize d3d9.dll\n");
        CoTaskMemFree(This);
        return VFW_E_DDRAW_CAPS_NOT_SUITABLE;
    }

    i = 0;
    do
    {
        D3DDISPLAYMODE mode;

        hr = IDirect3D9_EnumAdapterModes(This->d3d9_ptr, i++, D3DFMT_X8R8G8B8, 0, &mode);
	if (hr == D3DERR_INVALIDCALL) break; /* out of adapters */
    } while (FAILED(hr));
    if (FAILED(hr))
        ERR("HR: %08x\n", hr);
    if (hr == D3DERR_NOTAVAILABLE)
    {
        ERR("Format not supported\n");
        IDirect3D9_Release(This->d3d9_ptr);
        CoTaskMemFree(This);
        return VFW_E_DDRAW_CAPS_NOT_SUITABLE;
    }

    This->IVMRImagePresenter9_iface.lpVtbl = &VMR9_ImagePresenter;
    This->IVMRSurfaceAllocatorEx9_iface.lpVtbl = &VMR9_SurfaceAllocator;

    This->refCount = 1;
    This->pVMR9 = parent;
    This->d3d9_surfaces = NULL;
    This->d3d9_dev = NULL;
    This->hMon = 0;
    This->d3d9_vertex = NULL;
    This->num_surfaces = 0;
    This->hWndThread = NULL;
    This->ack = CreateEventW(NULL, 0, 0, NULL);
    This->SurfaceAllocatorNotify = NULL;
    This->reset = FALSE;

    *ppv = &This->IVMRImagePresenter9_iface;
    return S_OK;
}