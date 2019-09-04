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
struct TYPE_3__ {int ref; int /*<<< orphan*/ * lpVtbl; int /*<<< orphan*/  bDirectSound8; } ;
typedef  scalar_t__ LPDIRECTSOUND8 ;
typedef  int /*<<< orphan*/  LPCGUID ;
typedef  TYPE_1__* LPCDirectSoundImpl ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  CDirectSoundImpl ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,scalar_t__) ; 
 scalar_t__ DSERR_INVALIDPARAM ; 
 scalar_t__ DSERR_OUTOFMEMORY ; 
 scalar_t__ DS_OK ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IDirectSound8_Initialize (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectSound8_Release (scalar_t__) ; 
 int /*<<< orphan*/  SUCCEEDED (scalar_t__) ; 
 int /*<<< orphan*/  vt_DirectSound8 ; 

HRESULT
InternalDirectSoundCreate(
    LPCGUID lpcGUID,
    LPDIRECTSOUND8 *ppDS,
    IUnknown *pUnkOuter,
    BOOL bDirectSound8)
{
    LPCDirectSoundImpl This;
    HRESULT hr;

    if (!ppDS || pUnkOuter != NULL)
    {
        /* invalid parameter passed */
        return DSERR_INVALIDPARAM;
    }

    /* allocate CDirectSoundImpl struct */
    This = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(CDirectSoundImpl));
    if (!This)
    {
        /* not enough memory */
        return DSERR_OUTOFMEMORY;
    }

    /* initialize IDirectSound object */
    This->ref = 1;
    This->bDirectSound8 = bDirectSound8;
    This->lpVtbl = &vt_DirectSound8;


    /* initialize direct sound interface */
    hr = IDirectSound8_Initialize((LPDIRECTSOUND8)&This->lpVtbl, lpcGUID);

    /* check for success */
    if (!SUCCEEDED(hr))
    {
        /* failed */
        DPRINT("Failed to initialize DirectSound object with %x\n", hr);
        IDirectSound8_Release((LPDIRECTSOUND8)&This->lpVtbl);
        return hr;
    }

    /* store result */
    *ppDS = (LPDIRECTSOUND8)&This->lpVtbl;
    DPRINT("DirectSound object %p\n", *ppDS);
    return DS_OK;
}