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
struct TYPE_5__ {int Opcode; } ;
struct TYPE_6__ {TYPE_1__ GenHeader; } ;
typedef  TYPE_2__ _SlResponseHeader_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_306 ; 
 int /*<<< orphan*/  SL_ERROR_TRACE2 (int /*<<< orphan*/ ,char*,int,int) ; 
#define  SL_OPCODE_DEVICE_ABORT 131 
#define  SL_OPCODE_DEVICE_DEVICEASYNCFATALERROR 130 
#define  SL_OPCODE_DEVICE_INITCOMPLETE 129 
#define  SL_OPCODE_DEVICE_STOP_ASYNC_RESPONSE 128 
 int /*<<< orphan*/  _sl_HandleAsync_InitComplete (TYPE_2__*) ; 
 int /*<<< orphan*/  _sl_HandleAsync_Stop (TYPE_2__*) ; 

void _SlDrvDeviceEventHandler(void* pArgs)
{
    _SlResponseHeader_t      *pHdr       = (_SlResponseHeader_t *)pArgs;

    switch(pHdr->GenHeader.Opcode)
    {
    case SL_OPCODE_DEVICE_INITCOMPLETE:
        _sl_HandleAsync_InitComplete(pHdr);
        break;
    case SL_OPCODE_DEVICE_STOP_ASYNC_RESPONSE:
        _sl_HandleAsync_Stop(pHdr);
        break;


		case SL_OPCODE_DEVICE_ABORT:
			{
#if defined (sl_GeneralEvtHdlr) || defined(EXT_LIB_REGISTERED_GENERAL_EVENTS)
				SlDeviceEvent_t      devHandler;
				devHandler.Event = SL_DEVICE_ABORT_ERROR_EVENT;	
				devHandler.EventData.deviceReport.AbortType = *((_u32*)pArgs + 2);
				devHandler.EventData.deviceReport.AbortData = *((_u32*)pArgs + 3);
				_SlDrvHandleGeneralEvents(&devHandler);
#endif		
			}
        break;

    case  SL_OPCODE_DEVICE_DEVICEASYNCFATALERROR:
#if defined (sl_GeneralEvtHdlr) || defined(EXT_LIB_REGISTERED_GENERAL_EVENTS)
        {
            _BasicResponse_t     *pMsgArgs   = (_BasicResponse_t *)_SL_RESP_ARGS_START(pHdr);
            SlDeviceEvent_t      devHandler;
            devHandler.Event = SL_DEVICE_FATAL_ERROR_EVENT;
            devHandler.EventData.deviceEvent.status = pMsgArgs->status & 0xFF;
            devHandler.EventData.deviceEvent.sender = (SlErrorSender_e)((pMsgArgs->status >> 8) & 0xFF);
            _SlDrvHandleGeneralEvents(&devHandler);
        }
#endif
        break;
    default:
        SL_ERROR_TRACE2(MSG_306, "ASSERT: _SlDrvDeviceEventHandler : invalid opcode = 0x%x = %1", pHdr->GenHeader.Opcode, pHdr->GenHeader.Opcode);
    }
}