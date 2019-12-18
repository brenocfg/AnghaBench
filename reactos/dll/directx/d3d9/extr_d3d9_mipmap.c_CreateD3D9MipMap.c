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
typedef  void* UINT ;
struct TYPE_2__ {int /*<<< orphan*/ * lpVtbl; int /*<<< orphan*/  Format; void* dwHeight; void* dwWidth; int /*<<< orphan*/  Usage; int /*<<< orphan*/  BaseTexture; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  TYPE_1__* LPD3D9MIPMAP ;
typedef  int /*<<< orphan*/  IDirect3DTexture9 ;
typedef  int /*<<< orphan*/  IDirect3DBaseTexture9Vtbl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  DIRECT3DDEVICE9_INT ;
typedef  int /*<<< orphan*/  D3DPOOL ;
typedef  int /*<<< orphan*/  D3DFORMAT ;
typedef  int /*<<< orphan*/  D3D9MipMap ;

/* Variables and functions */
 int /*<<< orphan*/  AlignedAlloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  D3D9MipMap_Vtbl ; 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitDirect3DBaseTexture9 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_EXTERNAL ; 
 int /*<<< orphan*/  UNIMPLEMENTED ; 

HRESULT CreateD3D9MipMap(DIRECT3DDEVICE9_INT* pDevice, UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture)
{
    LPD3D9MIPMAP pThisTexture;
    if (FAILED(AlignedAlloc((LPVOID*)&pThisTexture, sizeof(D3D9MipMap))))
    {
        DPRINT1("Could not create D3D9MipMap");
        return E_OUTOFMEMORY;
    }

    InitDirect3DBaseTexture9(&pThisTexture->BaseTexture, (IDirect3DBaseTexture9Vtbl*)&D3D9MipMap_Vtbl, Usage, Levels, Format, Pool, pDevice, RT_EXTERNAL);

    pThisTexture->lpVtbl = &D3D9MipMap_Vtbl;
    
    pThisTexture->Usage = Usage;
    pThisTexture->dwWidth = Width;
    pThisTexture->dwHeight = Height;
    pThisTexture->Format = Format;

    *ppTexture = (IDirect3DTexture9*)&pThisTexture->lpVtbl;

    UNIMPLEMENTED;
    return D3D_OK;
}