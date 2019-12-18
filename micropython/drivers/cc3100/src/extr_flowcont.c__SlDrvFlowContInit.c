#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  TxSyncObj; int /*<<< orphan*/  TxLockObj; int /*<<< orphan*/  TxPoolCnt; } ;
struct TYPE_4__ {TYPE_1__ FlowContCB; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_CONT_MIN ; 
 int /*<<< orphan*/  OSI_RET_OK_CHECK (int /*<<< orphan*/ ) ; 
 TYPE_2__* g_pCB ; 
 int /*<<< orphan*/  sl_LockObjCreate (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sl_SyncObjCreate (int /*<<< orphan*/ *,char*) ; 

void _SlDrvFlowContInit(void)
{
    g_pCB->FlowContCB.TxPoolCnt = FLOW_CONT_MIN;

    OSI_RET_OK_CHECK(sl_LockObjCreate(&g_pCB->FlowContCB.TxLockObj, "TxLockObj"));

    OSI_RET_OK_CHECK(sl_SyncObjCreate(&g_pCB->FlowContCB.TxSyncObj, "TxSyncObj"));
}