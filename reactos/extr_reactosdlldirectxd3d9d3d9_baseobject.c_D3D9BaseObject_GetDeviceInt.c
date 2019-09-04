#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pUnknown; } ;
typedef  int /*<<< orphan*/  LPDIRECT3DDEVICE9 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DIRECT3DDEVICE9_INT ;
typedef  TYPE_1__ D3D9BaseObject ;

/* Variables and functions */
 int /*<<< orphan*/  D3DERR_INVALIDCALL ; 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  E_NOINTERFACE ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * IDirect3DDevice9ToImpl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IDirect3DDevice9 ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (scalar_t__,int /*<<< orphan*/ *,void**) ; 

HRESULT D3D9BaseObject_GetDeviceInt(D3D9BaseObject* pBaseObject, DIRECT3DDEVICE9_INT** ppDevice)
{
    if (NULL == ppDevice)
        return D3DERR_INVALIDCALL;

    *ppDevice = NULL;

    if (pBaseObject->pUnknown)
    {
        LPDIRECT3DDEVICE9 pDevice;
        if (FAILED(IUnknown_QueryInterface(pBaseObject->pUnknown, &IID_IDirect3DDevice9, (void**)&pDevice)))
            return E_NOINTERFACE;

        *ppDevice = IDirect3DDevice9ToImpl(pDevice);
        return D3D_OK;
    }

    return E_NOINTERFACE;
}