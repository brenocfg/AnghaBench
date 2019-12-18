#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int ref; int /*<<< orphan*/  tid; int /*<<< orphan*/  msiHandle; TYPE_2__ IProvideMultipleClassInfo_iface; TYPE_1__ IDispatch_iface; } ;
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ AutomationObject ;

/* Variables and functions */
 int /*<<< orphan*/  AutomationObjectVtbl ; 
 int /*<<< orphan*/  ProvideMultipleClassInfoVtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_riid_from_tid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT init_automation_object(AutomationObject *This, MSIHANDLE msiHandle, tid_t tid)
{
    TRACE("(%p, %d, %s)\n", This, msiHandle, debugstr_guid(get_riid_from_tid(tid)));

    This->IDispatch_iface.lpVtbl = &AutomationObjectVtbl;
    This->IProvideMultipleClassInfo_iface.lpVtbl = &ProvideMultipleClassInfoVtbl;
    This->ref = 1;

    This->msiHandle = msiHandle;
    This->tid = tid;

    return S_OK;
}