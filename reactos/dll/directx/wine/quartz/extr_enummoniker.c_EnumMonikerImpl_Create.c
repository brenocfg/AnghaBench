#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int ref; int nMonikerCount; TYPE_1__ IEnumMoniker_iface; scalar_t__ index; void* ppMoniker; } ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  TYPE_1__ IEnumMoniker ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ EnumMonikerImpl ;

/* Variables and functions */
 void* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  EnumMonikerImpl_Vtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ **,int,TYPE_1__**) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ **,int) ; 

HRESULT EnumMonikerImpl_Create(IMoniker ** ppMoniker, ULONG nMonikerCount, IEnumMoniker ** ppEnum)
{
    /* NOTE: assumes that array of IMonikers has already been AddRef'd
     * I.e. this function does not AddRef the array of incoming
     * IMonikers */
    EnumMonikerImpl * pemi = CoTaskMemAlloc(sizeof(EnumMonikerImpl));

    TRACE("(%p, %d, %p)\n", ppMoniker, nMonikerCount, ppEnum);

    *ppEnum = NULL;

    if (!pemi)
        return E_OUTOFMEMORY;

    pemi->IEnumMoniker_iface.lpVtbl = &EnumMonikerImpl_Vtbl;
    pemi->ref = 1;
    pemi->ppMoniker = CoTaskMemAlloc(nMonikerCount * sizeof(IMoniker*));
    memcpy(pemi->ppMoniker, ppMoniker, nMonikerCount*sizeof(IMoniker*));
    pemi->nMonikerCount = nMonikerCount;
    pemi->index = 0;

    *ppEnum = &pemi->IEnumMoniker_iface;

    return S_OK;
}