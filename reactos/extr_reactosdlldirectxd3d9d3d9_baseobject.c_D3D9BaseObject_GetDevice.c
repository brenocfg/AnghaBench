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
typedef  int /*<<< orphan*/  IDirect3DDevice9 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ D3D9BaseObject ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOINTERFACE ; 
 int /*<<< orphan*/  IID_IDirect3DDevice9 ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (scalar_t__,int /*<<< orphan*/ *,void**) ; 

HRESULT D3D9BaseObject_GetDevice(D3D9BaseObject* pBaseObject, IDirect3DDevice9** ppDevice)
{
    if (pBaseObject->pUnknown)
    {
        return IUnknown_QueryInterface(pBaseObject->pUnknown, &IID_IDirect3DDevice9, (void**)ppDevice);
    }

    return E_NOINTERFACE;
}