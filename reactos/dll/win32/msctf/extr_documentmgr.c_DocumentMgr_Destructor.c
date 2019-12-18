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
struct TYPE_5__ {int /*<<< orphan*/  CompartmentMgr; int /*<<< orphan*/  TransitoryExtensionSink; scalar_t__* contextStack; int /*<<< orphan*/  ITfDocumentMgr_iface; } ;
typedef  int /*<<< orphan*/  ITfThreadMgr ;
typedef  TYPE_1__ DocumentMgr ;

/* Variables and functions */
 int /*<<< orphan*/  CompartmentMgr_Destructor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ITfContext_Release (scalar_t__) ; 
 int /*<<< orphan*/  ITfThreadMgr_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TF_GetThreadMgr (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  ThreadMgr_OnDocumentMgrDestruction (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_sinks (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DocumentMgr_Destructor(DocumentMgr *This)
{
    ITfThreadMgr *tm = NULL;
    TRACE("destroying %p\n", This);

    TF_GetThreadMgr(&tm);
    if (tm)
    {
        ThreadMgr_OnDocumentMgrDestruction(tm, &This->ITfDocumentMgr_iface);
        ITfThreadMgr_Release(tm);
    }

    if (This->contextStack[0])
        ITfContext_Release(This->contextStack[0]);
    if (This->contextStack[1])
        ITfContext_Release(This->contextStack[1]);
    free_sinks(&This->TransitoryExtensionSink);
    CompartmentMgr_Destructor(This->CompartmentMgr);
    HeapFree(GetProcessHeap(),0,This);
}