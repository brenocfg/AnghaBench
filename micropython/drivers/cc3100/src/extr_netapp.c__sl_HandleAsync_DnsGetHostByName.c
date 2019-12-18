#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  _GetHostByNameIPv6AsyncResponse_t ;
typedef  int /*<<< orphan*/  _GetHostByNameIPv4AsyncResponse_t ;
struct TYPE_6__ {size_t ActionIndex; } ;
struct TYPE_7__ {TYPE_2__ AsyncExt; } ;
struct TYPE_8__ {TYPE_3__ FunctionParams; TYPE_1__* ObjPool; } ;
struct TYPE_5__ {int AdditionalData; int /*<<< orphan*/  SyncObj; int /*<<< orphan*/ * pRespArgs; } ;

/* Variables and functions */
 int SL_NETAPP_FAMILY_MASK ; 
 int /*<<< orphan*/  VERIFY_SOCKET_CB (int) ; 
 scalar_t__ _SL_RESP_ARGS_START (void*) ; 
 int /*<<< orphan*/  _SlDrvProtectionObjLockWaitForever () ; 
 int /*<<< orphan*/  _SlDrvProtectionObjUnLock () ; 
 int /*<<< orphan*/  _SlDrvSyncObjSignal (int /*<<< orphan*/ *) ; 
 TYPE_4__* g_pCB ; 
 int /*<<< orphan*/  sl_Memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void _sl_HandleAsync_DnsGetHostByName(void *pVoidBuf)
{
    _GetHostByNameIPv4AsyncResponse_t     *pMsgArgs   = (_GetHostByNameIPv4AsyncResponse_t *)_SL_RESP_ARGS_START(pVoidBuf);

   _SlDrvProtectionObjLockWaitForever();

    VERIFY_SOCKET_CB(NULL != g_pCB->ObjPool[g_pCB->FunctionParams.AsyncExt.ActionIndex].pRespArgs);

	/*IPv6 */
	if(g_pCB->ObjPool[g_pCB->FunctionParams.AsyncExt.ActionIndex].AdditionalData & SL_NETAPP_FAMILY_MASK)
	{
		sl_Memcpy(g_pCB->ObjPool[g_pCB->FunctionParams.AsyncExt.ActionIndex].pRespArgs, pMsgArgs, sizeof(_GetHostByNameIPv6AsyncResponse_t));
	}
	/*IPv4 */
	else
	{
		sl_Memcpy(g_pCB->ObjPool[g_pCB->FunctionParams.AsyncExt.ActionIndex].pRespArgs, pMsgArgs, sizeof(_GetHostByNameIPv4AsyncResponse_t));
	}
	_SlDrvSyncObjSignal(&g_pCB->ObjPool[g_pCB->FunctionParams.AsyncExt.ActionIndex].SyncObj);
    _SlDrvProtectionObjUnLock();
    return;
}