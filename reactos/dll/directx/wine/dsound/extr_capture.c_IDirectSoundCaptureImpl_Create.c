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
struct TYPE_3__ {int /*<<< orphan*/ * device; scalar_t__ ref; int /*<<< orphan*/ * lpVtbl; } ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUNDCAPTURE8 ;
typedef  TYPE_1__ IDirectSoundCaptureImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DSERR_OUTOFMEMORY ; 
 int /*<<< orphan*/  DS_OK ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  dscvt ; 

__attribute__((used)) static HRESULT IDirectSoundCaptureImpl_Create(
    LPDIRECTSOUNDCAPTURE8 * ppDSC)
{
    IDirectSoundCaptureImpl *pDSC;
    TRACE("(%p)\n", ppDSC);

    /* Allocate memory */
    pDSC = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(IDirectSoundCaptureImpl));
    if (pDSC == NULL) {
        WARN("out of memory\n");
        *ppDSC = NULL;
        return DSERR_OUTOFMEMORY;
    }

    pDSC->lpVtbl = &dscvt;
    pDSC->ref    = 0;
    pDSC->device = NULL;

    *ppDSC = (LPDIRECTSOUNDCAPTURE8)pDSC;

    return DS_OK;
}