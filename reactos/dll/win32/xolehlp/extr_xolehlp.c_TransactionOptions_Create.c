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
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; TYPE_2__ ITransactionOptions_iface; } ;
typedef  TYPE_1__ TransactionOptions ;
typedef  TYPE_2__ ITransactionOptions ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TransactionOptions_Vtbl ; 

__attribute__((used)) static HRESULT TransactionOptions_Create(ITransactionOptions **ppv)
{
    TransactionOptions *This;

    if (!ppv) return E_INVALIDARG;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(TransactionOptions));
    if (!This) return E_OUTOFMEMORY;

    This->ITransactionOptions_iface.lpVtbl = &TransactionOptions_Vtbl;
    This->ref = 1;

    *ppv = &This->ITransactionOptions_iface;

    return S_OK;
}