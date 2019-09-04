#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t _u8 ;
typedef  int /*<<< orphan*/  _SlReturnVal_t ;
typedef  scalar_t__ _SlOpcode_t ;
struct TYPE_10__ {scalar_t__ ActionAsyncOpcode; int /*<<< orphan*/  AsyncEventHandler; } ;
struct TYPE_6__ {size_t ActionIndex; int /*<<< orphan*/  AsyncEvtHandler; } ;
struct TYPE_7__ {TYPE_1__ AsyncExt; } ;
struct TYPE_9__ {size_t ActivePoolIdx; TYPE_3__* ObjPool; TYPE_2__ FunctionParams; } ;
struct TYPE_8__ {int AdditionalData; scalar_t__ ActionID; size_t NextIndex; } ;

/* Variables and functions */
 size_t BSD_SOCKET_ID_MASK ; 
 size_t MAX_CONCURRENT_ACTIONS ; 
 size_t MAX_SOCKET_ENUM_IDX ; 
 scalar_t__ RECV_ID ; 
 size_t SL_MAX_SOCKETS ; 
 int SL_NETAPP_FAMILY_MASK ; 
 scalar_t__ SL_OPCODE_IPV6 ; 
 scalar_t__ SL_OPCODE_SOCKET_RECVASYNCRESPONSE ; 
 scalar_t__ SL_OPCODE_SOCKET_RECVFROMASYNCRESPONSE ; 
 scalar_t__ SL_OPCODE_SOCKET_RECVFROMASYNCRESPONSE_V6 ; 
 int /*<<< orphan*/  SL_RET_CODE_OK ; 
 int /*<<< orphan*/  SL_RET_CODE_SELF_ERROR ; 
 TYPE_5__* _SlActionLookupTable ; 
 TYPE_4__* g_pCB ; 

_SlReturnVal_t _SlFindAndSetActiveObj(_SlOpcode_t  Opcode, _u8 Sd)
{
    _u8 ActiveIndex;

    ActiveIndex = g_pCB->ActivePoolIdx;
    /* go over the active list if exist to find obj waiting for this Async event */
#ifndef SL_TINY_EXT    
		while (MAX_CONCURRENT_ACTIONS > ActiveIndex)
#else
        /* Only one Active action is availabe in tiny mode, so we can replace the loop with if condition */
        if (MAX_CONCURRENT_ACTIONS > ActiveIndex)
#endif
    {
        /* unset the Ipv4\IPv6 bit in the opcode if family bit was set  */
        if (g_pCB->ObjPool[ActiveIndex].AdditionalData & SL_NETAPP_FAMILY_MASK)
        {
            Opcode &= ~SL_OPCODE_IPV6;
        }

        if ((g_pCB->ObjPool[ActiveIndex].ActionID == RECV_ID) && (Sd == g_pCB->ObjPool[ActiveIndex].AdditionalData) && 
						( (SL_OPCODE_SOCKET_RECVASYNCRESPONSE == Opcode) || (SL_OPCODE_SOCKET_RECVFROMASYNCRESPONSE == Opcode)
#ifndef SL_TINY_EXT
                        || (SL_OPCODE_SOCKET_RECVFROMASYNCRESPONSE_V6 == Opcode) 
#endif
                          ) 

               )
        {
            g_pCB->FunctionParams.AsyncExt.ActionIndex = ActiveIndex;
            return SL_RET_CODE_OK;
        }
        /* In case this action is socket related, SocketID is in use, otherwise will be set to SL_MAX_SOCKETS */
        if ( (_SlActionLookupTable[ g_pCB->ObjPool[ActiveIndex].ActionID - MAX_SOCKET_ENUM_IDX].ActionAsyncOpcode == Opcode) && 
            ( ((Sd == (g_pCB->ObjPool[ActiveIndex].AdditionalData & BSD_SOCKET_ID_MASK) ) && (SL_MAX_SOCKETS > Sd)) || (SL_MAX_SOCKETS == (g_pCB->ObjPool[ActiveIndex].AdditionalData & BSD_SOCKET_ID_MASK)) ) )
        {
            /* set handler */
            g_pCB->FunctionParams.AsyncExt.AsyncEvtHandler = _SlActionLookupTable[ g_pCB->ObjPool[ActiveIndex].ActionID - MAX_SOCKET_ENUM_IDX].AsyncEventHandler;
            g_pCB->FunctionParams.AsyncExt.ActionIndex = ActiveIndex;
            return SL_RET_CODE_OK;
        }
        ActiveIndex = g_pCB->ObjPool[ActiveIndex].NextIndex;
    }

    return SL_RET_CODE_SELF_ERROR;

 

}