#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_18__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_6__ USBH_HandleTypeDef ;
struct TYPE_15__ {int /*<<< orphan*/  data; } ;
struct TYPE_16__ {TYPE_3__ payload; } ;
struct TYPE_14__ {void* param1; } ;
struct TYPE_17__ {int req_state; TYPE_4__ data_container; int /*<<< orphan*/ * object_ptr; int /*<<< orphan*/  iteration; TYPE_2__ resp_container; int /*<<< orphan*/  state; int /*<<< orphan*/  transaction_id; int /*<<< orphan*/  session_id; int /*<<< orphan*/  data_packet; int /*<<< orphan*/  data_packet_counter; int /*<<< orphan*/  data_length; int /*<<< orphan*/ * data_ptr; int /*<<< orphan*/  flags; } ;
struct TYPE_20__ {TYPE_5__ ptp; } ;
struct TYPE_19__ {int Nparam; void* Param3; void* Param2; void* Param1; int /*<<< orphan*/  Transaction_ID; int /*<<< orphan*/  SessionID; int /*<<< orphan*/  Code; } ;
struct TYPE_13__ {TYPE_8__* pData; } ;
typedef  TYPE_7__ PTP_ContainerTypedef ;
typedef  TYPE_8__ MTP_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  PTP_DP_GETDATA ; 
 int /*<<< orphan*/  PTP_OC_GetPartialObject ; 
 int /*<<< orphan*/  PTP_OP_REQUEST_STATE ; 
#define  PTP_REQ_SEND 129 
#define  PTP_REQ_WAIT 128 
 int /*<<< orphan*/  USBH_BUSY ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_PTP_Process (TYPE_6__*) ; 
 int /*<<< orphan*/  USBH_PTP_SendRequest (TYPE_6__*,TYPE_7__*) ; 
 int /*<<< orphan*/  USBH_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

USBH_StatusTypeDef USBH_PTP_GetPartialObject(USBH_HandleTypeDef *phost, 
                                           uint32_t handle, 
                                           uint32_t offset,
                                           uint32_t maxbytes, 
                                           uint8_t *object,
                                           uint32_t *len)
{
  USBH_StatusTypeDef   status = USBH_BUSY; 
  MTP_HandleTypeDef    *MTP_Handle =  phost->pActiveClass->pData; 
  PTP_ContainerTypedef  ptp_container;
  
  switch(MTP_Handle->ptp.req_state)
  {
  case PTP_REQ_SEND:

    /* Set operation request type */
    MTP_Handle->ptp.flags = PTP_DP_GETDATA;
    MTP_Handle->ptp.data_ptr = (uint8_t *)&(MTP_Handle->ptp.data_container);
    MTP_Handle->ptp.data_length = 0;
    MTP_Handle->ptp.data_packet_counter = 0;
    MTP_Handle->ptp.data_packet = 0;

    /* set object control params */
    MTP_Handle->ptp.object_ptr = object;
    
    /* Fill operation request params */      
    ptp_container.Code = PTP_OC_GetPartialObject;
    ptp_container.SessionID = MTP_Handle->ptp.session_id;
    ptp_container.Transaction_ID = MTP_Handle->ptp.transaction_id ++;
    ptp_container.Param1 = handle;  
    ptp_container.Param2 = offset;
    ptp_container.Param3 = maxbytes;   
    ptp_container.Nparam = 3;
    
    /* convert request packet into USB raw packet*/
    USBH_PTP_SendRequest (phost, &ptp_container); 
        
    /* Setup State machine and start transfer */
    MTP_Handle->ptp.state = PTP_OP_REQUEST_STATE;
    MTP_Handle->ptp.req_state = PTP_REQ_WAIT;
    status = USBH_BUSY; 
    break;
    
  case PTP_REQ_WAIT:
    status = USBH_PTP_Process(phost);
    
    if(status == USBH_OK)
    {
      *len = MTP_Handle->ptp.resp_container.param1;
      /* first packet is in the PTP data payload buffer */
      if(MTP_Handle->ptp.iteration == 0)
      {
        /* copy it to object */
        USBH_memcpy(MTP_Handle->ptp.object_ptr, MTP_Handle->ptp.data_container.payload.data, *len);
      }      
    }
    break;
    
  default:
    break;
  }
  return status;
}