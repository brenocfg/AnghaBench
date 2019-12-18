#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_13__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_3__ USBH_HandleTypeDef ;
struct TYPE_12__ {int req_state; int /*<<< orphan*/  state; int /*<<< orphan*/  transaction_id; int /*<<< orphan*/  session_id; int /*<<< orphan*/  data_packet; int /*<<< orphan*/  data_packet_counter; int /*<<< orphan*/  data_length; int /*<<< orphan*/  data_container; int /*<<< orphan*/ * data_ptr; int /*<<< orphan*/  flags; } ;
struct TYPE_15__ {TYPE_2__ ptp; } ;
struct TYPE_14__ {int Nparam; int /*<<< orphan*/  Param1; int /*<<< orphan*/  Transaction_ID; int /*<<< orphan*/  SessionID; int /*<<< orphan*/  Code; } ;
struct TYPE_11__ {TYPE_5__* pData; } ;
typedef  int /*<<< orphan*/  PTP_StorageInfoTypedef ;
typedef  TYPE_4__ PTP_ContainerTypedef ;
typedef  TYPE_5__ MTP_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  PTP_DP_GETDATA ; 
 int /*<<< orphan*/  PTP_GetStorageInfo (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTP_OC_GetStorageInfo ; 
 int /*<<< orphan*/  PTP_OP_REQUEST_STATE ; 
#define  PTP_REQ_SEND 129 
#define  PTP_REQ_WAIT 128 
 int /*<<< orphan*/  USBH_BUSY ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_PTP_Process (TYPE_3__*) ; 
 int /*<<< orphan*/  USBH_PTP_SendRequest (TYPE_3__*,TYPE_4__*) ; 

USBH_StatusTypeDef USBH_PTP_GetStorageInfo (USBH_HandleTypeDef *phost, uint32_t storage_id, PTP_StorageInfoTypedef *storage_info)
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
   
    /* Fill operation request params */      
    ptp_container.Code = PTP_OC_GetStorageInfo;
    ptp_container.SessionID = MTP_Handle->ptp.session_id;
    ptp_container.Transaction_ID = MTP_Handle->ptp.transaction_id ++;
    ptp_container.Param1 = storage_id;    
    ptp_container.Nparam = 1;
    
    /* convert request packet inti USB raw packet*/
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
      PTP_GetStorageInfo (phost, storage_id, storage_info);
    }
    break;
    
  default:
    break;
  }
  return status;
}