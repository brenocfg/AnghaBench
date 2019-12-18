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
struct TYPE_6__ {int /*<<< orphan*/  cs; } ;
struct TYPE_5__ {unsigned int refs; int /*<<< orphan*/  entry; int /*<<< orphan*/  rw_lock; } ;
typedef  TYPE_1__ RpcContextHandle ;
typedef  TYPE_2__ RpcAssoc ;
typedef  scalar_t__ NDR_SCONTEXT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RpcContextHandle_Destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  RtlReleaseResource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 

unsigned int RpcServerAssoc_ReleaseContextHandle(RpcAssoc *assoc, NDR_SCONTEXT SContext, BOOL release_lock)
{
    RpcContextHandle *context_handle = (RpcContextHandle *)SContext;
    unsigned int refs;

    if (release_lock)
        RtlReleaseResource(&context_handle->rw_lock);

    EnterCriticalSection(&assoc->cs);
    refs = --context_handle->refs;
    if (!refs)
        list_remove(&context_handle->entry);
    LeaveCriticalSection(&assoc->cs);

    if (!refs)
        RpcContextHandle_Destroy(context_handle);

    return refs;
}