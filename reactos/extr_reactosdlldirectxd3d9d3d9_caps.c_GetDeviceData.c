#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * pSupportedQueriesList; scalar_t__ NumSupportedQueries; int /*<<< orphan*/ * pSupportedExtendedModes; scalar_t__ NumSupportedExtendedModes; int /*<<< orphan*/ * pSupportedFormatOps; scalar_t__ NumSupportedFormatOps; int /*<<< orphan*/  dwRefreshRate; int /*<<< orphan*/  DisplayFormat; int /*<<< orphan*/  RawDisplayFormat; int /*<<< orphan*/  dwDisplayHeight; int /*<<< orphan*/  dwDisplayWidth; } ;
struct TYPE_6__ {TYPE_2__ DriverCaps; int /*<<< orphan*/  hD3DRefDll; int /*<<< orphan*/  szDeviceName; int /*<<< orphan*/  D3D9Callbacks; int /*<<< orphan*/ * pUnknown6BC; int /*<<< orphan*/  DeviceType; int /*<<< orphan*/  hDC; } ;
typedef  int /*<<< orphan*/ * LPDDSURFACEDESC ;
typedef  TYPE_1__* LPD3D9_DEVICEDATA ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  DDSURFACEDESC ;
typedef  int /*<<< orphan*/  DDPIXELFORMAT ;
typedef  int /*<<< orphan*/  D3DQUERYTYPE ;
typedef  int /*<<< orphan*/  D3DHAL_GLOBALDRIVERDATA ;
typedef  int /*<<< orphan*/  D3DHAL_D3DEXTENDEDCAPS ;
typedef  int /*<<< orphan*/  D3DDISPLAYMODE ;
typedef  TYPE_2__ D3D9_DRIVERCAPS ;
typedef  int /*<<< orphan*/  D3D9_CALLBACKS ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CanReenableDirectDrawObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateInternalDeviceData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetD3D9DriverInfo (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseInternalDeviceData (TYPE_1__*) ; 
 scalar_t__ TRUE ; 
 int max (scalar_t__,int) ; 

BOOL GetDeviceData(LPD3D9_DEVICEDATA pDeviceData)
{
    BOOL bRet;
    D3DHAL_GLOBALDRIVERDATA GlobalDriverData;
    D3DHAL_D3DEXTENDEDCAPS D3dExtendedCaps;
    LPDDSURFACEDESC puD3dTextureFormats;
    DDPIXELFORMAT* pD3dZStencilFormatList;
    D3DDISPLAYMODE* pD3dDisplayModeList;
    D3DQUERYTYPE* pD3dQueryList;
    DWORD NumTextureFormats = 0;
    DWORD NumStencilFormats = 0;
    DWORD NumExtendedFormats = 0;
    DWORD NumQueries = 0;

    if (NULL == pDeviceData->pUnknown6BC)
    {
        CreateInternalDeviceData(
            pDeviceData->hDC,
            pDeviceData->szDeviceName,
            &pDeviceData->pUnknown6BC,
            pDeviceData->DeviceType,
            &pDeviceData->hD3DRefDll
            );

        if (NULL == pDeviceData->pUnknown6BC)
        {
            DPRINT1("Failed to create DirectDrawObject for Direct3D9");
            return FALSE;
        }
    }
    else
    {
        D3D9_DRIVERCAPS DriverCaps;
        D3D9_CALLBACKS D3D9Callbacks;

        if (FALSE == CanReenableDirectDrawObject(pDeviceData->pUnknown6BC))
        {
            DPRINT1("Failed to re-enable DirectDrawObject");
            return FALSE;
        }

        bRet = GetD3D9DriverInfo(
            pDeviceData->pUnknown6BC,
            &DriverCaps,
            &D3D9Callbacks,
            pDeviceData->szDeviceName,
            pDeviceData->hD3DRefDll,
            &GlobalDriverData,
            &D3dExtendedCaps,
            NULL,
            NULL,
            NULL,
            NULL,
            &NumTextureFormats,
            &NumStencilFormats,
            &NumExtendedFormats,
            &NumQueries
            );

        if (TRUE == bRet)
        {
            pDeviceData->DriverCaps.dwDisplayWidth = DriverCaps.dwDisplayWidth;
            pDeviceData->DriverCaps.dwDisplayHeight = DriverCaps.dwDisplayHeight;
            pDeviceData->DriverCaps.RawDisplayFormat = DriverCaps.RawDisplayFormat;
            pDeviceData->DriverCaps.DisplayFormat = DriverCaps.DisplayFormat;
            pDeviceData->DriverCaps.dwRefreshRate = DriverCaps.dwRefreshRate;
        }

        return bRet;
    }

    /* Cleanup of old stuff */
    if (pDeviceData->DriverCaps.pSupportedFormatOps)
    {
        HeapFree(GetProcessHeap(), 0, pDeviceData->DriverCaps.pSupportedFormatOps);
        pDeviceData->DriverCaps.pSupportedFormatOps = NULL;
    }
    if (pDeviceData->DriverCaps.pSupportedExtendedModes)
    {
        HeapFree(GetProcessHeap(), 0, pDeviceData->DriverCaps.pSupportedExtendedModes);
        pDeviceData->DriverCaps.pSupportedExtendedModes = NULL;
    }
    if (pDeviceData->DriverCaps.pSupportedQueriesList)
    {
        HeapFree(GetProcessHeap(), 0, pDeviceData->DriverCaps.pSupportedQueriesList);
        pDeviceData->DriverCaps.pSupportedQueriesList = NULL;
    }

    if (FALSE == CanReenableDirectDrawObject(pDeviceData->pUnknown6BC))
    {
        DPRINT1("Failed to re-enable DirectDrawObject");
        ReleaseInternalDeviceData(pDeviceData);
        return FALSE;
    }

    bRet = GetD3D9DriverInfo(
        pDeviceData->pUnknown6BC,
        &pDeviceData->DriverCaps,
        &pDeviceData->D3D9Callbacks,
        pDeviceData->szDeviceName,
        pDeviceData->hD3DRefDll,
        &GlobalDriverData,
        &D3dExtendedCaps,
        NULL,
        NULL,
        NULL,
        NULL,
        &NumTextureFormats,
        &NumStencilFormats,
        &NumExtendedFormats,
        &NumQueries
        );

    if (FALSE == bRet)
    {
        DPRINT1("Could not query DirectDrawObject, aborting");
        ReleaseInternalDeviceData(pDeviceData);
        return FALSE;
    }

    puD3dTextureFormats = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, max(NumTextureFormats, 1) * sizeof(DDSURFACEDESC));
    pD3dZStencilFormatList = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, max(NumStencilFormats, 1) * sizeof(DDPIXELFORMAT));
    pD3dDisplayModeList = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, max(NumExtendedFormats, 1) * sizeof(D3DDISPLAYMODE));
    pD3dQueryList = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, max(NumQueries, 1) * sizeof(D3DQUERYTYPE));

    bRet = GetD3D9DriverInfo(
        pDeviceData->pUnknown6BC,
        &pDeviceData->DriverCaps,
        &pDeviceData->D3D9Callbacks,
        pDeviceData->szDeviceName,
        pDeviceData->hD3DRefDll,
        &GlobalDriverData,
        &D3dExtendedCaps,
        puD3dTextureFormats,
        pD3dZStencilFormatList,
        pD3dDisplayModeList,
        pD3dQueryList,
        &NumTextureFormats,
        &NumStencilFormats,
        &NumExtendedFormats,
        &NumQueries
        );

    if (FALSE == bRet)
    {
        DPRINT1("Could not query DirectDrawObject, aborting");
        HeapFree(GetProcessHeap(), 0, puD3dTextureFormats);
        HeapFree(GetProcessHeap(), 0, pD3dZStencilFormatList);
        HeapFree(GetProcessHeap(), 0, pD3dDisplayModeList);
        HeapFree(GetProcessHeap(), 0, pD3dQueryList);
        ReleaseInternalDeviceData(pDeviceData);
        return FALSE;
    }

    pDeviceData->DriverCaps.NumSupportedFormatOps = NumTextureFormats;
    if (NumTextureFormats > 0)
        pDeviceData->DriverCaps.pSupportedFormatOps = puD3dTextureFormats;

    pDeviceData->DriverCaps.NumSupportedExtendedModes = NumExtendedFormats;
    if (NumExtendedFormats > 0)
        pDeviceData->DriverCaps.pSupportedExtendedModes = pD3dDisplayModeList;

    pDeviceData->DriverCaps.NumSupportedQueries = NumQueries;
    if (NumQueries > 0)
        pDeviceData->DriverCaps.pSupportedQueriesList = pD3dQueryList;
    
    HeapFree(GetProcessHeap(), 0, pD3dZStencilFormatList); 

    return TRUE;
}