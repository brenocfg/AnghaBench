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
struct TYPE_3__ {int /*<<< orphan*/ * manager; int /*<<< orphan*/  connected; int /*<<< orphan*/  ITextStoreACPSink_iface; scalar_t__ pITextStoreACP; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  ITfDocumentMgr ;
typedef  int /*<<< orphan*/  ITfContext ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  IID_ITextStoreACPSink ; 
 int /*<<< orphan*/  ITextStoreACP_AdviseSink (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TS_AS_ALL_SINKS ; 
 TYPE_1__* impl_from_ITfContext (int /*<<< orphan*/ *) ; 

HRESULT Context_Initialize(ITfContext *iface, ITfDocumentMgr *manager)
{
    Context *This = impl_from_ITfContext(iface);

    if (This->pITextStoreACP)
        ITextStoreACP_AdviseSink(This->pITextStoreACP, &IID_ITextStoreACPSink,
            (IUnknown*)&This->ITextStoreACPSink_iface, TS_AS_ALL_SINKS);
    This->connected = TRUE;
    This->manager = manager;
    return S_OK;
}