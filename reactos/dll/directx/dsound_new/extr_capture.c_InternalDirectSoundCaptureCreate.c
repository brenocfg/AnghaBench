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
struct TYPE_3__ {int ref; int /*<<< orphan*/ * lpVtbl; } ;
typedef  scalar_t__ LPDIRECTSOUNDCAPTURE8 ;
typedef  int /*<<< orphan*/  LPDIRECTSOUND8 ;
typedef  int /*<<< orphan*/  LPCGUID ;
typedef  TYPE_1__* LPCDirectSoundCaptureImpl ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  CDirectSoundCaptureImpl ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,scalar_t__) ; 
 scalar_t__ DSERR_INVALIDPARAM ; 
 scalar_t__ DSERR_OUTOFMEMORY ; 
 scalar_t__ DS_OK ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IDirectSoundCapture_Initialize (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectSoundCapture_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUCCEEDED (scalar_t__) ; 
 int /*<<< orphan*/  vt_DirectSoundCapture ; 

HRESULT
InternalDirectSoundCaptureCreate(
    LPCGUID lpcGUID,
    LPDIRECTSOUNDCAPTURE8 *ppDS,
    IUnknown *pUnkOuter)
{
    LPCDirectSoundCaptureImpl This;
    HRESULT hr;

    if (!ppDS || pUnkOuter != NULL)
    {
        /* invalid parameter passed */
        return DSERR_INVALIDPARAM;
    }

    /* allocate CDirectSoundCaptureImpl struct */
    This = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(CDirectSoundCaptureImpl));
    if (!This)
    {
        /* not enough memory */
        return DSERR_OUTOFMEMORY;
    }

    /* initialize IDirectSoundCapture object */
    This->ref = 1;
    This->lpVtbl = &vt_DirectSoundCapture;


    /* initialize direct sound interface */
    hr = IDirectSoundCapture_Initialize((LPDIRECTSOUNDCAPTURE8)&This->lpVtbl, lpcGUID);

    /* check for success */
    if (!SUCCEEDED(hr))
    {
        /* failed */
        DPRINT("Failed to initialize DirectSoundCapture object with %x\n", hr);
        IDirectSoundCapture_Release((LPDIRECTSOUND8)&This->lpVtbl);
        return hr;
    }

    /* store result */
    *ppDS = (LPDIRECTSOUNDCAPTURE8)&This->lpVtbl;
    DPRINT("DirectSoundCapture object %p\n", *ppDS);
    return DS_OK;
}