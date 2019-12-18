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
struct TYPE_6__ {int /*<<< orphan*/  cs; int /*<<< orphan*/  context_handle_list; } ;
struct TYPE_5__ {int refs; int /*<<< orphan*/  entry; int /*<<< orphan*/  rw_lock; void* ctx_guard; } ;
typedef  TYPE_1__ RpcContextHandle ;
typedef  TYPE_2__ RpcAssoc ;
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  scalar_t__ NDR_SCONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  RPC_S_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  RtlAcquireResourceExclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlInitializeResource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

RPC_STATUS RpcServerAssoc_AllocateContextHandle(RpcAssoc *assoc, void *CtxGuard,
                                                NDR_SCONTEXT *SContext)
{
    RpcContextHandle *context_handle;

    context_handle = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*context_handle));
    if (!context_handle)
        return RPC_S_OUT_OF_MEMORY;

    context_handle->ctx_guard = CtxGuard;
    RtlInitializeResource(&context_handle->rw_lock);
    context_handle->refs = 1;

    /* lock here to mirror unmarshall, so we don't need to special-case the
     * freeing of a non-marshalled context handle */
    RtlAcquireResourceExclusive(&context_handle->rw_lock, TRUE);

    EnterCriticalSection(&assoc->cs);
    list_add_tail(&assoc->context_handle_list, &context_handle->entry);
    LeaveCriticalSection(&assoc->cs);

    *SContext = (NDR_SCONTEXT)context_handle;
    return RPC_S_OK;
}