#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  CompartmentMgr; int /*<<< orphan*/  pTextLayoutSink; int /*<<< orphan*/  pTextEditSink; int /*<<< orphan*/  pStatusSink; int /*<<< orphan*/  pEditTransactionSink; int /*<<< orphan*/  pContextKeyEventSink; scalar_t__ defaultCookie; scalar_t__ pITfContextOwnerCompositionSink; scalar_t__ pITextStoreACP; } ;
typedef  TYPE_1__ EditCookie ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  CompartmentMgr_Destructor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ITextStoreACP_Release (scalar_t__) ; 
 int /*<<< orphan*/  ITfContextOwnerCompositionSink_Release (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  free_sinks (int /*<<< orphan*/ *) ; 
 TYPE_1__* remove_Cookie (scalar_t__) ; 

__attribute__((used)) static void Context_Destructor(Context *This)
{
    EditCookie *cookie;
    TRACE("destroying %p\n", This);

    if (This->pITextStoreACP)
        ITextStoreACP_Release(This->pITextStoreACP);

    if (This->pITfContextOwnerCompositionSink)
        ITfContextOwnerCompositionSink_Release(This->pITfContextOwnerCompositionSink);

    if (This->defaultCookie)
    {
        cookie = remove_Cookie(This->defaultCookie);
        HeapFree(GetProcessHeap(),0,cookie);
        This->defaultCookie = 0;
    }

    free_sinks(&This->pContextKeyEventSink);
    free_sinks(&This->pEditTransactionSink);
    free_sinks(&This->pStatusSink);
    free_sinks(&This->pTextEditSink);
    free_sinks(&This->pTextLayoutSink);

    CompartmentMgr_Destructor(This->CompartmentMgr);
    HeapFree(GetProcessHeap(),0,This);
}