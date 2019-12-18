#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ _u16 ;
typedef  int /*<<< orphan*/  _i8 ;
struct TYPE_10__ {scalar_t__ TextLen; int /*<<< orphan*/  Status; int /*<<< orphan*/  Port; int /*<<< orphan*/  Address; } ;
typedef  TYPE_4__ _GetHostByServiceIPv4AsyncResponse_t ;
struct TYPE_11__ {scalar_t__* inout_TextLen; int /*<<< orphan*/  out_pText; int /*<<< orphan*/  Status; int /*<<< orphan*/ * out_pPort; int /*<<< orphan*/ * out_pAddr; } ;
typedef  TYPE_5__ _GetHostByServiceAsyncResponse_t ;
struct TYPE_8__ {size_t ActionIndex; } ;
struct TYPE_9__ {TYPE_2__ AsyncExt; } ;
struct TYPE_12__ {TYPE_3__ FunctionParams; TYPE_1__* ObjPool; } ;
struct TYPE_7__ {int AdditionalData; int /*<<< orphan*/  SyncObj; int /*<<< orphan*/ * pRespArgs; } ;

/* Variables and functions */
 int SL_NETAPP_FAMILY_MASK ; 
 int /*<<< orphan*/  VERIFY_SOCKET_CB (int) ; 
 scalar_t__ _SL_RESP_ARGS_START (void*) ; 
 int /*<<< orphan*/  _SlDrvSyncObjSignal (int /*<<< orphan*/ *) ; 
 TYPE_6__* g_pCB ; 
 int /*<<< orphan*/  sl_Memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

void _sl_HandleAsync_DnsGetHostByService(void *pVoidBuf)
{

	_GetHostByServiceAsyncResponse_t* Res;
	_u16 				  TextLen;
	_u16 				  UserTextLen;


	/*pVoidBuf - is point to opcode of the event.*/
    
	/*set pMsgArgs to point to the attribute of the event.*/
	_GetHostByServiceIPv4AsyncResponse_t   *pMsgArgs   = (_GetHostByServiceIPv4AsyncResponse_t *)_SL_RESP_ARGS_START(pVoidBuf);

    VERIFY_SOCKET_CB(NULL != g_pCB->ObjPool[g_pCB->FunctionParams.AsyncExt.ActionIndex].pRespArgs);

	/*IPv6*/
	if(g_pCB->ObjPool[g_pCB->FunctionParams.AsyncExt.ActionIndex].AdditionalData & SL_NETAPP_FAMILY_MASK)
	{
		return;
	}
	/*IPv4*/
	else
	{
    /*************************************************************************************************
	
	1. Copy the attribute part of the evnt to the attribute part of the response
	sl_Memcpy(g_pCB->GetHostByServiceCB.pAsyncRsp, pMsgArgs, sizeof(_GetHostByServiceIPv4AsyncResponse_t));

    set to TextLen the text length of the service.*/
	TextLen = pMsgArgs->TextLen;
	
	/*Res pointed to mDNS global object struct */
		Res = (_GetHostByServiceAsyncResponse_t*)g_pCB->ObjPool[g_pCB->FunctionParams.AsyncExt.ActionIndex].pRespArgs;



	/*It is 4 bytes so we avoid from memcpy*/
	Res->out_pAddr[0]	= pMsgArgs->Address;
	Res->out_pPort[0]	= pMsgArgs->Port;
	Res->Status			= pMsgArgs->Status;
	
	/*set to TextLen the text length of the user (input fromthe user).*/
	UserTextLen			= Res->inout_TextLen[0];
    
	/*Cut the service text if the user requested for smaller text.*/
	UserTextLen = (TextLen <= UserTextLen) ? TextLen : UserTextLen;
	Res->inout_TextLen[0] = UserTextLen ;

    /**************************************************************************************************

	2. Copy the payload part of the evnt (the text) to the payload part of the response
	the lenght of the copy is according to the text length in the attribute part. */
	

	sl_Memcpy(Res->out_pText          ,
		     (_i8 *)(& pMsgArgs[1])  ,   /* & pMsgArgs[1] -> 1st byte after the fixed header = 1st byte of variable text.*/
			 UserTextLen              );


    /**************************************************************************************************/

		_SlDrvSyncObjSignal(&g_pCB->ObjPool[g_pCB->FunctionParams.AsyncExt.ActionIndex].SyncObj);
		return;
	}
}