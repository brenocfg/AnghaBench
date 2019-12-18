#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int DeviceType; int /*<<< orphan*/  NumberOfAdaptersInGroup; int /*<<< orphan*/  AdapterOrdinalInGroup; int /*<<< orphan*/  MasterAdapterOrdinal; } ;
struct TYPE_9__ {TYPE_3__ DriverCaps9; } ;
struct TYPE_10__ {int /*<<< orphan*/  NumAdaptersInGroup; int /*<<< orphan*/  AdapterIndexInGroup; int /*<<< orphan*/  MasterAdapterIndex; TYPE_1__ DriverCaps; } ;
typedef  TYPE_2__* LPDIRECT3D9_DISPLAYADAPTER ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int D3DDEVTYPE ;
typedef  TYPE_3__ D3DCAPS9 ;

/* Variables and functions */
 int /*<<< orphan*/  CopyDriverCaps (TYPE_3__*,TYPE_3__*) ; 
#define  D3DDEVTYPE_HAL 131 
#define  D3DDEVTYPE_NULLREF 130 
#define  D3DDEVTYPE_REF 129 
#define  D3DDEVTYPE_SW 128 
 int /*<<< orphan*/  D3DERR_INVALIDDEVICE ; 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIMPLEMENTED ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_3__*,int) ; 

HRESULT GetAdapterCaps(const LPDIRECT3D9_DISPLAYADAPTER pDisplayAdapter, D3DDEVTYPE DeviceType, D3DCAPS9* pDstCaps)
{
    HRESULT hResult = D3DERR_INVALIDDEVICE;
    D3DCAPS9* pDriverCaps = NULL;

    ZeroMemory(pDstCaps, sizeof(D3DCAPS9));

    switch (DeviceType)
    {
    case D3DDEVTYPE_HAL:
        pDriverCaps = &pDisplayAdapter->DriverCaps.DriverCaps9;
        hResult = D3D_OK;
        break;

    case D3DDEVTYPE_REF:
    case D3DDEVTYPE_SW:
    case D3DDEVTYPE_NULLREF:
        UNIMPLEMENTED;
        hResult = D3D_OK;
        break;

    default:
        DPRINT1("Unknown DeviceType argument");
        break;
    }

    if (pDriverCaps != NULL)
    {
        CopyDriverCaps(pDriverCaps, pDstCaps);
    }

    if (SUCCEEDED(hResult))
    {
        pDstCaps->DeviceType = DeviceType;
        pDstCaps->MasterAdapterOrdinal = pDisplayAdapter->MasterAdapterIndex;
        pDstCaps->AdapterOrdinalInGroup = pDisplayAdapter->AdapterIndexInGroup;
        pDstCaps->NumberOfAdaptersInGroup = pDisplayAdapter->NumAdaptersInGroup;
    }

    return hResult;
}