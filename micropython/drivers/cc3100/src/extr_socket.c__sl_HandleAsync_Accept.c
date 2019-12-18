#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int sd; } ;
struct TYPE_12__ {TYPE_4__ IpV4; } ;
typedef  TYPE_5__ _SocketAddrResponse_u ;
struct TYPE_9__ {size_t ActionIndex; } ;
struct TYPE_10__ {TYPE_2__ AsyncExt; } ;
struct TYPE_13__ {TYPE_3__ FunctionParams; TYPE_1__* ObjPool; } ;
struct TYPE_8__ {int /*<<< orphan*/  SyncObj; int /*<<< orphan*/ * pRespArgs; } ;

/* Variables and functions */
 int BSD_SOCKET_ID_MASK ; 
 int SL_MAX_SOCKETS ; 
 int /*<<< orphan*/  VERIFY_PROTOCOL (int) ; 
 int /*<<< orphan*/  VERIFY_SOCKET_CB (int) ; 
 scalar_t__ _SL_RESP_ARGS_START (void*) ; 
 int /*<<< orphan*/  _SlDrvProtectionObjLockWaitForever () ; 
 int /*<<< orphan*/  _SlDrvProtectionObjUnLock () ; 
 int /*<<< orphan*/  _SlDrvSyncObjSignal (int /*<<< orphan*/ *) ; 
 TYPE_7__* g_pCB ; 
 int /*<<< orphan*/  sl_Memcpy (int /*<<< orphan*/ *,TYPE_5__*,int) ; 

void _sl_HandleAsync_Accept(void *pVoidBuf)
{
    _SocketAddrResponse_u      *pMsgArgs   = (_SocketAddrResponse_u *)_SL_RESP_ARGS_START(pVoidBuf);

    _SlDrvProtectionObjLockWaitForever();

    VERIFY_PROTOCOL(( pMsgArgs->IpV4.sd & BSD_SOCKET_ID_MASK) <= SL_MAX_SOCKETS);
    VERIFY_SOCKET_CB(NULL != g_pCB->ObjPool[g_pCB->FunctionParams.AsyncExt.ActionIndex].pRespArgs);

	sl_Memcpy(g_pCB->ObjPool[g_pCB->FunctionParams.AsyncExt.ActionIndex].pRespArgs, pMsgArgs,sizeof(_SocketAddrResponse_u));
	_SlDrvSyncObjSignal(&g_pCB->ObjPool[g_pCB->FunctionParams.AsyncExt.ActionIndex].SyncObj);

    _SlDrvProtectionObjUnLock();
    return;
}