#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* itemDelimiter; struct TYPE_5__* itemName; scalar_t__ pMarshal; } ;
typedef  TYPE_1__ ItemMonikerImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IUnknown_Release (scalar_t__) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 

__attribute__((used)) static HRESULT ItemMonikerImpl_Destroy(ItemMonikerImpl* This)
{
    TRACE("(%p)\n",This);

    if (This->pMarshal) IUnknown_Release(This->pMarshal);
    HeapFree(GetProcessHeap(),0,This->itemName);
    HeapFree(GetProcessHeap(),0,This->itemDelimiter);
    HeapFree(GetProcessHeap(),0,This);

    return S_OK;
}