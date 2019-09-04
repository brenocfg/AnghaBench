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
struct _Direct3DDevice9_INT {int dummy; } ;
typedef  enum REF_TYPE { ____Placeholder_REF_TYPE } REF_TYPE ;
typedef  void* UINT ;
struct TYPE_3__ {int wPaletteIndex; int Usage; int bIsAutoGenMipMap; int /*<<< orphan*/  FilterType; void* MipMapLevels2; void* MipMapLevels; int /*<<< orphan*/  Format; int /*<<< orphan*/ * lpVtbl; int /*<<< orphan*/  BaseResource; } ;
typedef  int /*<<< orphan*/  IDirect3DBaseTexture9Vtbl ;
typedef  TYPE_1__ Direct3DBaseTexture9_INT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  D3DPOOL ;
typedef  int /*<<< orphan*/  D3DFORMAT ;

/* Variables and functions */
 int /*<<< orphan*/  D3DTEXF_LINEAR ; 
 int D3DUSAGE_AUTOGENMIPMAP ; 
 int /*<<< orphan*/  InitDirect3DResource9 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct _Direct3DDevice9_INT*,int) ; 

void InitDirect3DBaseTexture9(Direct3DBaseTexture9_INT* pBaseTexture,
                              IDirect3DBaseTexture9Vtbl* pVtbl,
                              DWORD Usage,
                              UINT Levels,
                              D3DFORMAT Format,
                              D3DPOOL Pool,
                              struct _Direct3DDevice9_INT* pDevice,
                              enum REF_TYPE RefType)
{
    InitDirect3DResource9(&pBaseTexture->BaseResource, Pool, pDevice, RefType);

    pBaseTexture->lpVtbl = pVtbl;
    pBaseTexture->Format = Format;
    pBaseTexture->wPaletteIndex = 0xFFFF;
    pBaseTexture->Usage = Usage;
    pBaseTexture->MipMapLevels = Levels;
    pBaseTexture->MipMapLevels2 = Levels;

    pBaseTexture->FilterType = D3DTEXF_LINEAR;
    pBaseTexture->bIsAutoGenMipMap = (Usage & D3DUSAGE_AUTOGENMIPMAP) != 0;
}