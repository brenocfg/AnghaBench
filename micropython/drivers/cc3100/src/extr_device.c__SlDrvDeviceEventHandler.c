#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  void* _u32 ;
struct TYPE_15__ {int Opcode; } ;
struct TYPE_16__ {TYPE_4__ GenHeader; } ;
typedef  TYPE_5__ _SlResponseHeader_t ;
struct TYPE_17__ {int status; } ;
typedef  TYPE_6__ _BasicResponse_t ;
struct TYPE_13__ {int status; int /*<<< orphan*/  sender; } ;
struct TYPE_12__ {void* AbortData; void* AbortType; } ;
struct TYPE_14__ {TYPE_2__ deviceEvent; TYPE_1__ deviceReport; } ;
struct TYPE_18__ {TYPE_3__ EventData; int /*<<< orphan*/  Event; } ;
typedef  int /*<<< orphan*/  SlErrorSender_e ;
typedef  TYPE_7__ SlDeviceEvent_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_306 ; 
 int /*<<< orphan*/  SL_DEVICE_ABORT_ERROR_EVENT ; 
 int /*<<< orphan*/  SL_DEVICE_FATAL_ERROR_EVENT ; 
 int /*<<< orphan*/  SL_ERROR_TRACE2 (int /*<<< orphan*/ ,char*,int,int) ; 
#define  SL_OPCODE_DEVICE_ABORT 131 
#define  SL_OPCODE_DEVICE_DEVICEASYNCFATALERROR 130 
#define  SL_OPCODE_DEVICE_INITCOMPLETE 129 
#define  SL_OPCODE_DEVICE_STOP_ASYNC_RESPONSE 128 
 scalar_t__ _SL_RESP_ARGS_START (TYPE_5__*) ; 
 int /*<<< orphan*/  _SlDrvHandleGeneralEvents (TYPE_7__*) ; 
 int /*<<< orphan*/  _sl_HandleAsync_InitComplete (TYPE_5__*) ; 
 int /*<<< orphan*/  _sl_HandleAsync_Stop (TYPE_5__*) ; 

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