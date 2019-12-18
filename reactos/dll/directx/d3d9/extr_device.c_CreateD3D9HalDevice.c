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
struct IDirect3DDevice9 {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPDIRECT3DDEVICE9_INT ;
typedef  int /*<<< orphan*/  LPDIRECT3D9_INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  D3DPRESENT_PARAMETERS ;
typedef  int /*<<< orphan*/  D3D9HALDEVICE ;

/* Variables and functions */
 int /*<<< orphan*/  AlignedAlloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  AlignedFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D3DDEVTYPE_HAL ; 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  DDERR_OUTOFMEMORY ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitD3D9BaseDevice (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

HRESULT CreateD3D9HalDevice(LPDIRECT3D9_INT pDirect3D9, UINT Adapter,
                            HWND hFocusWindow, DWORD BehaviourFlags,
                            D3DPRESENT_PARAMETERS* pPresentationParameters,
                            DWORD NumAdaptersToCreate,
                            struct IDirect3DDevice9** ppReturnedDeviceInterface)
{
    HRESULT Ret;

    if (FAILED(AlignedAlloc((LPVOID *)ppReturnedDeviceInterface, sizeof(D3D9HALDEVICE))))
    {
        DPRINT1("Not enough memory to create HAL device");
        return DDERR_OUTOFMEMORY;
    }

    Ret = InitD3D9BaseDevice((LPDIRECT3DDEVICE9_INT)*ppReturnedDeviceInterface, pDirect3D9, Adapter,
                             D3DDEVTYPE_HAL, hFocusWindow, BehaviourFlags,
                             pPresentationParameters, NumAdaptersToCreate);

    if (FAILED(Ret))
    {
        AlignedFree((LPVOID)*ppReturnedDeviceInterface);
        return Ret;
    }

    return D3D_OK;
}