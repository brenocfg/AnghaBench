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
struct TYPE_6__ {int ref; int tabSize; int currentPos; TYPE_1__ IEnumMoniker_iface; int /*<<< orphan*/ ** tabMoniker; } ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  TYPE_1__ IEnumMoniker ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ EnumMonikerImpl ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  IMoniker_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STG_E_INSUFFICIENTMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  VT_EnumMonikerImpl ; 

__attribute__((used)) static HRESULT
EnumMonikerImpl_CreateEnumMoniker(IMoniker** tabMoniker, ULONG tabSize,
               ULONG currentPos, BOOL leftToRight, IEnumMoniker ** ppmk)
{
    EnumMonikerImpl* newEnumMoniker;
    ULONG i;

    if (currentPos > tabSize)
        return E_INVALIDARG;

    newEnumMoniker = HeapAlloc(GetProcessHeap(), 0, sizeof(EnumMonikerImpl));

    if (newEnumMoniker == 0)
        return STG_E_INSUFFICIENTMEMORY;

    /* Initialize the virtual function table. */
    newEnumMoniker->IEnumMoniker_iface.lpVtbl = &VT_EnumMonikerImpl;
    newEnumMoniker->ref          = 1;

    newEnumMoniker->tabSize=tabSize;
    newEnumMoniker->currentPos=currentPos;

    newEnumMoniker->tabMoniker=HeapAlloc(GetProcessHeap(),0,tabSize*sizeof(newEnumMoniker->tabMoniker[0]));

    if (newEnumMoniker->tabMoniker==NULL) {
        HeapFree(GetProcessHeap(), 0, newEnumMoniker);
        return E_OUTOFMEMORY;
    }

    if (leftToRight)
        for (i=0;i<tabSize;i++){

            newEnumMoniker->tabMoniker[i]=tabMoniker[i];
            IMoniker_AddRef(tabMoniker[i]);
        }
    else
        for (i = tabSize; i > 0; i--){

            newEnumMoniker->tabMoniker[tabSize-i]=tabMoniker[i - 1];
            IMoniker_AddRef(tabMoniker[i - 1]);
        }

    *ppmk=&newEnumMoniker->IEnumMoniker_iface;

    return S_OK;
}