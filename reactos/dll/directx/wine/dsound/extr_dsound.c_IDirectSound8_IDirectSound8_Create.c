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
struct TYPE_3__ {int /*<<< orphan*/ * pds; scalar_t__ ref; int /*<<< orphan*/ * lpVtbl; } ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUND8 ;
typedef  TYPE_1__ IDirectSound8_IDirectSound8 ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DSERR_INVALIDPARAM ; 
 int /*<<< orphan*/  DSERR_OUTOFMEMORY ; 
 int /*<<< orphan*/  DS_OK ; 
 int /*<<< orphan*/  DirectSound8_DirectSound8_Vtbl ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDirectSoundImpl_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  WARN (char*) ; 

__attribute__((used)) static HRESULT IDirectSound8_IDirectSound8_Create(
    LPDIRECTSOUND8 pds,
    LPDIRECTSOUND8 * ppds)
{
    IDirectSound8_IDirectSound8 * pdsds;
    TRACE("(%p,%p)\n",pds,ppds);

    if (ppds == NULL) {
        ERR("invalid parameter: ppds == NULL\n");
        return DSERR_INVALIDPARAM;
    }

    if (pds == NULL) {
        ERR("invalid parameter: pds == NULL\n");
        *ppds = NULL;
        return DSERR_INVALIDPARAM;
    }

    pdsds = HeapAlloc(GetProcessHeap(),0,sizeof(*pdsds));
    if (pdsds == NULL) {
        WARN("out of memory\n");
        *ppds = NULL;
        return DSERR_OUTOFMEMORY;
    }

    pdsds->lpVtbl = &DirectSound8_DirectSound8_Vtbl;
    pdsds->ref = 0;
    pdsds->pds = pds;

    IDirectSoundImpl_AddRef(pds);
    *ppds = (LPDIRECTSOUND8)pdsds;

    return DS_OK;
}