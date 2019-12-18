#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_17__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_5__ USBH_HandleTypeDef ;
struct TYPE_14__ {int /*<<< orphan*/  data; } ;
struct TYPE_15__ {TYPE_2__ payload; } ;
struct TYPE_16__ {int req_state; int /*<<< orphan*/  data_length; int /*<<< orphan*/  state; int /*<<< orphan*/  transaction_id; int /*<<< orphan*/  session_id; int /*<<< orphan*/  object_ptr; TYPE_3__ data_container; int /*<<< orphan*/  data_packet; int /*<<< orphan*/  data_packet_counter; int /*<<< orphan*/ * data_ptr; int /*<<< orphan*/  flags; } ;
struct TYPE_19__ {TYPE_4__ ptp; } ;
struct TYPE_18__ {int Param2; int Param3; int Param4; int Param5; int Nparam; int /*<<< orphan*/  Param1; int /*<<< orphan*/  Transaction_ID; int /*<<< orphan*/  SessionID; int /*<<< orphan*/  Code; } ;
struct TYPE_13__ {TYPE_7__* pData; } ;
typedef  TYPE_6__ PTP_ContainerTypedef ;
typedef  int /*<<< orphan*/  MTP_PropertiesTypedef ;
typedef  TYPE_7__ MTP_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  PTP_DP_GETDATA ; 
 int /*<<< orphan*/  PTP_GetObjectPropList (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTP_OC_GetObjPropList ; 
 int /*<<< orphan*/  PTP_OP_REQUEST_STATE ; 
#define  PTP_REQ_SEND 129 
#define  PTP_REQ_WAIT 128 
 int /*<<< orphan*/  PTP_USB_BULK_PAYLOAD_LEN_READ ; 
 int /*<<< orphan*/  USBH_BUSY ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_PTP_Process (TYPE_5__*) ; 
 int /*<<< orphan*/  USBH_PTP_SendRequest (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  USBH_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

USBH_StatusTypeDef USBH_PTP_GetObjectPropList (USBH_HandleTypeDef *phost,
                                                uint32_t handle, 
                                                MTP_PropertiesTypedef *pprops, 
                                                uint32_t *nrofprops)
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
   
    /* copy first packet of the object into data container */
    USBH_memcpy(MTP_Handle->ptp.data_container.payload.data, MTP_Handle->ptp.object_ptr, PTP_USB_BULK_PAYLOAD_LEN_READ);
       
    /* Fill operation request params */      
    ptp_container.Code = PTP_OC_GetObjPropList;
    ptp_container.SessionID = MTP_Handle->ptp.session_id;
    ptp_container.Transaction_ID = MTP_Handle->ptp.transaction_id ++;
    ptp_container.Param1 = handle;  
    ptp_container.Param2 = 0x00000000U;  /* 0x00000000U should be "all formats" */
    ptp_container.Param3 = 0xFFFFFFFFU;  /* 0xFFFFFFFFU should be "all properties" */
    ptp_container.Param4 = 0x00000000U;
    ptp_container.Param5 = 0xFFFFFFFFU;  /* Return full tree below the Param1 handle */
    ptp_container.Nparam = 5;  
    
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
      PTP_GetObjectPropList (phost, pprops,  MTP_Handle->ptp.data_length);
    }
    break;
    
  default:
    break;
  }
  return status;
}