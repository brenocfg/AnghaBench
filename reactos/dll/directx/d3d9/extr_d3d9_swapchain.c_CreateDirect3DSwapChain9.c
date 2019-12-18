#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct _Direct3DDevice9_INT {TYPE_2__* DeviceData; int /*<<< orphan*/  lpVtbl; } ;
typedef  enum REF_TYPE { ____Placeholder_REF_TYPE } REF_TYPE ;
struct TYPE_5__ {int /*<<< orphan*/  lpVtbl; } ;
struct TYPE_7__ {size_t ChainIndex; size_t AdapterGroupIndex; scalar_t__ pUnknown015c; int /*<<< orphan*/  pUnknown6BC; int /*<<< orphan*/ * lpVtbl; TYPE_1__ BaseObject; } ;
struct TYPE_6__ {int /*<<< orphan*/  pUnknown6BC; } ;
typedef  scalar_t__ LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_3__ Direct3DSwapChain9_INT ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  D3D9BaseObject ;

/* Variables and functions */
 int /*<<< orphan*/  AlignedAlloc (scalar_t__*,int) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  Direct3DSwapChain9_Vtbl ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitD3D9BaseObject (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

Direct3DSwapChain9_INT* CreateDirect3DSwapChain9(enum REF_TYPE RefType, struct _Direct3DDevice9_INT* pBaseDevice, DWORD ChainIndex)
{
    Direct3DSwapChain9_INT* pThisSwapChain;
    if (FAILED(AlignedAlloc((LPVOID*)&pThisSwapChain, sizeof(Direct3DSwapChain9_INT))))
    {
        DPRINT1("Could not create Direct3DSwapChain9_INT");
        return NULL;
    }

    InitD3D9BaseObject((D3D9BaseObject*) &pThisSwapChain->BaseObject.lpVtbl, RefType, (IUnknown*) &pBaseDevice->lpVtbl);

    pThisSwapChain->lpVtbl = &Direct3DSwapChain9_Vtbl;

    pThisSwapChain->ChainIndex = ChainIndex;
    pThisSwapChain->AdapterGroupIndex = ChainIndex;
    pThisSwapChain->pUnknown6BC = pBaseDevice->DeviceData[ChainIndex].pUnknown6BC;
    pThisSwapChain->pUnknown015c = (LPVOID)0xD3D9D3D9;

    return pThisSwapChain;
}