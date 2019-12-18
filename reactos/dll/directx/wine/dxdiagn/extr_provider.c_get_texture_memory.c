#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dwCaps4; } ;
struct TYPE_5__ {int dwCaps; TYPE_1__ u1; scalar_t__ dwCaps3; scalar_t__ dwCaps2; } ;
typedef  int /*<<< orphan*/  IDirectDraw7 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_2__ DDSCAPS2 ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int DDSCAPS_LOCALVIDMEM ; 
 int DDSCAPS_VIDEOMEMORY ; 
 int /*<<< orphan*/  DirectDrawCreateEx (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IDirectDraw7_GetAvailableVidMem (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectDraw7_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDirectDraw7 ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL get_texture_memory(GUID *adapter, DWORD *available_mem)
{
    IDirectDraw7 *pDirectDraw;
    HRESULT hr;
    DDSCAPS2 dd_caps;

    hr = DirectDrawCreateEx(adapter, (void **)&pDirectDraw, &IID_IDirectDraw7, NULL);
    if (SUCCEEDED(hr))
    {
        dd_caps.dwCaps = DDSCAPS_LOCALVIDMEM | DDSCAPS_VIDEOMEMORY;
        dd_caps.dwCaps2 = dd_caps.dwCaps3 = dd_caps.u1.dwCaps4 = 0;
        hr = IDirectDraw7_GetAvailableVidMem(pDirectDraw, &dd_caps, available_mem, NULL);
        IDirectDraw7_Release(pDirectDraw);
        if (SUCCEEDED(hr))
            return TRUE;
    }

    return FALSE;
}