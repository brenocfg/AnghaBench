#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_11__ {int /*<<< orphan*/  RawDisplayFormat; int /*<<< orphan*/  dwRefreshRate; int /*<<< orphan*/  dwDisplayHeight; int /*<<< orphan*/  dwDisplayWidth; } ;
struct TYPE_14__ {TYPE_2__ DriverCaps; } ;
struct TYPE_13__ {TYPE_9__* DisplayAdapters; } ;
struct TYPE_12__ {int lRefCnt; size_t AdjustedBehaviourFlags; size_t BehaviourFlags; size_t NumAdaptersInDevice; int dwDXVersion; size_t* AdapterIndexInGroup; int /*<<< orphan*/ * pSwapChains; int /*<<< orphan*/ * pSwapChains2; TYPE_1__* CurrentDisplayMode; int /*<<< orphan*/ * DeviceData; int /*<<< orphan*/  hWnd; int /*<<< orphan*/  DeviceType; TYPE_4__* pDirect3D9; int /*<<< orphan*/  CriticalSection; int /*<<< orphan*/ * lpVtbl; int /*<<< orphan*/ * pUnknown; int /*<<< orphan*/  dwProcessId; int /*<<< orphan*/ * pResourceManager; } ;
struct TYPE_10__ {int /*<<< orphan*/  Format; int /*<<< orphan*/  RefreshRate; int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  TYPE_3__* LPDIRECT3DDEVICE9_INT ;
typedef  TYPE_4__* LPDIRECT3D9_INT ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  D3DPRESENT_PARAMETERS ;
typedef  int /*<<< orphan*/  D3DDEVTYPE ;
typedef  int /*<<< orphan*/  D3D9ResourceManager ;

/* Variables and functions */
 int /*<<< orphan*/  AlignedAlloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ CreateD3D9DeviceData (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateDirect3DSwapChain9 (int /*<<< orphan*/ ,TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  DDERR_GENERIC ; 
 int /*<<< orphan*/  DDERR_OUTOFMEMORY ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 int /*<<< orphan*/  Direct3DDevice9HAL_Vtbl ; 
 int /*<<< orphan*/  Direct3DSwapChain9_Init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetCurrentThreadId () ; 
 int /*<<< orphan*/  InitD3D9ResourceManager (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  InitializeCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RT_BUILTIN ; 

HRESULT InitD3D9BaseDevice(LPDIRECT3DDEVICE9_INT pThisBaseDevice, LPDIRECT3D9_INT pDirect3D9,
                           UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviourFlags,
                           D3DPRESENT_PARAMETERS* pPresentationParameters, DWORD NumAdaptersToCreate)
{
    D3D9ResourceManager* pResourceManager;
    DWORD i;

    // Insert Reset/Ctor here

    if (FAILED(AlignedAlloc((LPVOID *)&pResourceManager, sizeof(D3D9ResourceManager))) ||
        FAILED(InitD3D9ResourceManager(pResourceManager, pThisBaseDevice)))
    {
        DPRINT1("Could not create resource manager");
        return DDERR_OUTOFMEMORY;
    }

    pThisBaseDevice->pResourceManager = pResourceManager;

    pThisBaseDevice->lpVtbl = &Direct3DDevice9HAL_Vtbl;
    pThisBaseDevice->lRefCnt = 1;
    pThisBaseDevice->dwProcessId = GetCurrentThreadId();
    pThisBaseDevice->pUnknown = (IUnknown*) &pThisBaseDevice->lpVtbl;
    InitializeCriticalSection(&pThisBaseDevice->CriticalSection);

    pThisBaseDevice->pDirect3D9 = pDirect3D9;
    pThisBaseDevice->DeviceType = DeviceType;
    pThisBaseDevice->hWnd = hFocusWindow;
    pThisBaseDevice->AdjustedBehaviourFlags = BehaviourFlags;
    pThisBaseDevice->BehaviourFlags = BehaviourFlags;
    pThisBaseDevice->NumAdaptersInDevice = NumAdaptersToCreate;

    // TODO: Query driver for correct DX version
    pThisBaseDevice->dwDXVersion = 9;

    for (i = 0; i < NumAdaptersToCreate; i++)
    {
        if (FALSE == CreateD3D9DeviceData(&pDirect3D9->DisplayAdapters[i], &pThisBaseDevice->DeviceData[i]))
        {
            DPRINT1("Failed to get device data for adapter: %d", i);
            return DDERR_GENERIC;
        }

        pThisBaseDevice->AdapterIndexInGroup[i] = i;
        pThisBaseDevice->CurrentDisplayMode[i].Width = pDirect3D9->DisplayAdapters[i].DriverCaps.dwDisplayWidth;
        pThisBaseDevice->CurrentDisplayMode[i].Height = pDirect3D9->DisplayAdapters[i].DriverCaps.dwDisplayHeight;
        pThisBaseDevice->CurrentDisplayMode[i].RefreshRate = pDirect3D9->DisplayAdapters[i].DriverCaps.dwRefreshRate;
        pThisBaseDevice->CurrentDisplayMode[i].Format = pDirect3D9->DisplayAdapters[i].DriverCaps.RawDisplayFormat;

        pThisBaseDevice->pSwapChains[i] = CreateDirect3DSwapChain9(RT_BUILTIN, pThisBaseDevice, i);
        pThisBaseDevice->pSwapChains2[i] = pThisBaseDevice->pSwapChains[i];

        if (FAILED(Direct3DSwapChain9_Init(pThisBaseDevice->pSwapChains[i], pPresentationParameters)))
        {
            DPRINT1("Failed to init swap chain: %d", i);
            return DDERR_GENERIC;
        }
    }

    return D3D_OK;
}