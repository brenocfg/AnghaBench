#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int MaxSimultaneousTextures; TYPE_4__* pBaseDevice; int /*<<< orphan*/  pTextureHeap; } ;
struct TYPE_11__ {TYPE_3__* DeviceData; } ;
struct TYPE_8__ {int /*<<< orphan*/  MaxSimultaneousTextures; } ;
struct TYPE_9__ {TYPE_1__ DriverCaps9; } ;
struct TYPE_10__ {TYPE_2__ DriverCaps; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  TYPE_4__* LPDIRECT3DDEVICE9_INT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  TYPE_5__ D3D9ResourceManager ;

/* Variables and functions */
 int /*<<< orphan*/  AlignedAlloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  DDERR_OUTOFMEMORY ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int max (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT InitD3D9ResourceManager(D3D9ResourceManager* pThisResourceManager, LPDIRECT3DDEVICE9_INT pDirect3DDevice9)
{
    DWORD MaxSimultaneousTextures;

    MaxSimultaneousTextures = max(1, pDirect3DDevice9->DeviceData[0].DriverCaps.DriverCaps9.MaxSimultaneousTextures);

    if (FAILED(AlignedAlloc((LPVOID *)&pThisResourceManager->pTextureHeap, sizeof(DWORD) + MaxSimultaneousTextures * sizeof(int) * 3)))
    {
        DPRINT1("Could not allocate texture heap");
        return DDERR_OUTOFMEMORY;
    }

    // TODO: Init texture heap

    pThisResourceManager->MaxSimultaneousTextures = MaxSimultaneousTextures;
    pThisResourceManager->pBaseDevice = pDirect3DDevice9;

    return D3D_OK;
}