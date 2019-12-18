#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  USBH_URBStateTypeDef ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_22__ {int /*<<< orphan*/  os_event; TYPE_2__* pActiveClass; } ;
typedef  TYPE_6__ USBH_HandleTypeDef ;
struct TYPE_17__ {int /*<<< orphan*/  data; } ;
struct TYPE_19__ {int Flags; int /*<<< orphan*/  DataTransferLength; int /*<<< orphan*/  LUN; } ;
struct TYPE_20__ {TYPE_3__ field; int /*<<< orphan*/  data; } ;
struct TYPE_21__ {int state; int /*<<< orphan*/  cmd_state; TYPE_1__ csw; int /*<<< orphan*/  pbuf; TYPE_4__ cbw; } ;
struct TYPE_23__ {TYPE_5__ hbot; int /*<<< orphan*/  InPipe; int /*<<< orphan*/  OutPipe; int /*<<< orphan*/  OutEpSize; int /*<<< orphan*/  InEpSize; } ;
struct TYPE_18__ {TYPE_7__* pData; } ;
typedef  TYPE_7__ MSC_HandleTypeDef ;
typedef  int /*<<< orphan*/  BOT_CSWStatusTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  BOT_CBW_LENGTH ; 
 int /*<<< orphan*/  BOT_CMD_SEND ; 
 int /*<<< orphan*/  BOT_CSW_CMD_FAILED ; 
 int /*<<< orphan*/  BOT_CSW_CMD_PASSED ; 
 int /*<<< orphan*/  BOT_CSW_LENGTH ; 
#define  BOT_DATA_IN 138 
#define  BOT_DATA_IN_WAIT 137 
#define  BOT_DATA_OUT 136 
#define  BOT_DATA_OUT_WAIT 135 
 int /*<<< orphan*/  BOT_DIR_IN ; 
 int /*<<< orphan*/  BOT_DIR_OUT ; 
#define  BOT_ERROR_IN 134 
#define  BOT_ERROR_OUT 133 
#define  BOT_RECEIVE_CSW 132 
#define  BOT_RECEIVE_CSW_WAIT 131 
#define  BOT_SEND_CBW 130 
#define  BOT_SEND_CBW_WAIT 129 
#define  BOT_UNRECOVERED_ERROR 128 
 int /*<<< orphan*/  USBH_BUSY ; 
 int /*<<< orphan*/  USBH_BulkReceiveData (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_BulkSendData (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USBH_FAIL ; 
 int /*<<< orphan*/  USBH_LL_GetToggle (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_LL_GetURBState (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_LL_SetToggle (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_MSC_BOT_Abort (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_MSC_BOT_REQ_Reset (TYPE_6__*) ; 
 int /*<<< orphan*/  USBH_MSC_DecodeCSW (TYPE_6__*) ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_UNRECOVERED_ERROR ; 
 int /*<<< orphan*/  USBH_URB_DONE ; 
 int /*<<< orphan*/  USBH_URB_EVENT ; 
 int /*<<< orphan*/  USBH_URB_IDLE ; 
 int /*<<< orphan*/  USBH_URB_NOTREADY ; 
 int /*<<< orphan*/  USBH_URB_STALL ; 
 int USB_D2H ; 
 int USB_REQ_DIR_MASK ; 
 int /*<<< orphan*/  osMessagePut (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

USBH_StatusTypeDef USBH_MSC_BOT_Process (USBH_HandleTypeDef *phost, uint8_t lun)
{
  USBH_StatusTypeDef   status = USBH_BUSY;
  USBH_StatusTypeDef   error  = USBH_BUSY;  
  BOT_CSWStatusTypeDef CSW_Status = BOT_CSW_CMD_FAILED;
  USBH_URBStateTypeDef URB_Status = USBH_URB_IDLE;
  MSC_HandleTypeDef *MSC_Handle =  phost->pActiveClass->pData;
  uint8_t toggle = 0;
  
  switch (MSC_Handle->hbot.state)
  {
  case BOT_SEND_CBW:
    MSC_Handle->hbot.cbw.field.LUN = lun;
    MSC_Handle->hbot.state = BOT_SEND_CBW_WAIT;    
    USBH_BulkSendData (phost,
                       MSC_Handle->hbot.cbw.data, 
                       BOT_CBW_LENGTH, 
                       MSC_Handle->OutPipe,
                       1);
    
    break;
    
  case BOT_SEND_CBW_WAIT:
    
    URB_Status = USBH_LL_GetURBState(phost, MSC_Handle->OutPipe); 
    
    if(URB_Status == USBH_URB_DONE)
    { 
      if ( MSC_Handle->hbot.cbw.field.DataTransferLength != 0 )
      {
        /* If there is Data Transfer Stage */
        if (((MSC_Handle->hbot.cbw.field.Flags) & USB_REQ_DIR_MASK) == USB_D2H)
        {
          /* Data Direction is IN */
          MSC_Handle->hbot.state = BOT_DATA_IN;
        }
        else
        {
          /* Data Direction is OUT */
          MSC_Handle->hbot.state = BOT_DATA_OUT;
        } 
      }
      
      else
      {/* If there is NO Data Transfer Stage */
        MSC_Handle->hbot.state = BOT_RECEIVE_CSW;
      }
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_URB_EVENT, 0);
#endif   
    
    }   
    else if(URB_Status == USBH_URB_NOTREADY)
    {
      /* Re-send CBW */
      MSC_Handle->hbot.state = BOT_SEND_CBW;
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_URB_EVENT, 0);
#endif       
    }     
    else if(URB_Status == USBH_URB_STALL)
    {
      MSC_Handle->hbot.state  = BOT_ERROR_OUT;
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_URB_EVENT, 0);
#endif       
    }
    break;
    
  case BOT_DATA_IN:   
    /* Send first packet */        
    USBH_BulkReceiveData (phost,
                          MSC_Handle->hbot.pbuf, 
                          MSC_Handle->InEpSize , 
                          MSC_Handle->InPipe);
    
    MSC_Handle->hbot.state  = BOT_DATA_IN_WAIT;
    
    break;   
    
  case BOT_DATA_IN_WAIT:  
    
    URB_Status = USBH_LL_GetURBState(phost, MSC_Handle->InPipe); 
    
    if(URB_Status == USBH_URB_DONE) 
    {
      /* Adjudt Data pointer and data length */
      if(MSC_Handle->hbot.cbw.field.DataTransferLength > MSC_Handle->InEpSize)
      {
          MSC_Handle->hbot.pbuf += MSC_Handle->InEpSize;
          MSC_Handle->hbot.cbw.field.DataTransferLength -= MSC_Handle->InEpSize;  
      }
      else
      {
        MSC_Handle->hbot.cbw.field.DataTransferLength = 0;
      }
        
      /* More Data To be Received */
      if(MSC_Handle->hbot.cbw.field.DataTransferLength > 0)
      {
        /* Send next packet */        
        USBH_BulkReceiveData (phost,
                              MSC_Handle->hbot.pbuf, 
                              MSC_Handle->InEpSize , 
                              MSC_Handle->InPipe);
        
      }
      else
      {
        /* If value was 0, and successful transfer, then change the state */
        MSC_Handle->hbot.state  = BOT_RECEIVE_CSW;
#if (USBH_USE_OS == 1)
        osMessagePut ( phost->os_event, USBH_URB_EVENT, 0);
#endif 
      }
    }
    else if(URB_Status == USBH_URB_STALL)
    {
      /* This is Data IN Stage STALL Condition */
      MSC_Handle->hbot.state  = BOT_ERROR_IN;
      
      /* Refer to USB Mass-Storage Class : BOT (www.usb.org) 
      6.7.2 Host expects to receive data from the device
      3. On a STALL condition receiving data, then:
      The host shall accept the data received.
      The host shall clear the Bulk-In pipe.
      4. The host shall attempt to receive a CSW.*/
      
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_URB_EVENT, 0);
#endif       
    }     
    break;  
    
  case BOT_DATA_OUT:
    
    USBH_BulkSendData (phost,
                       MSC_Handle->hbot.pbuf, 
                       MSC_Handle->OutEpSize , 
                       MSC_Handle->OutPipe,
                       1);
    
    
    MSC_Handle->hbot.state  = BOT_DATA_OUT_WAIT;
    break;
    
  case BOT_DATA_OUT_WAIT:
    URB_Status = USBH_LL_GetURBState(phost, MSC_Handle->OutPipe);     
    
    if(URB_Status == USBH_URB_DONE)
    {
      /* Adjudt Data pointer and data length */
      if(MSC_Handle->hbot.cbw.field.DataTransferLength > MSC_Handle->OutEpSize)
      {
          MSC_Handle->hbot.pbuf += MSC_Handle->OutEpSize;
          MSC_Handle->hbot.cbw.field.DataTransferLength -= MSC_Handle->OutEpSize; 
      }
      else
      {
        MSC_Handle->hbot.cbw.field.DataTransferLength = 0;
      } 
      
      /* More Data To be Sent */
      if(MSC_Handle->hbot.cbw.field.DataTransferLength > 0)
      {
        USBH_BulkSendData (phost,
                           MSC_Handle->hbot.pbuf, 
                           MSC_Handle->OutEpSize , 
                           MSC_Handle->OutPipe,
                           1);
      }
      else
      {
        /* If value was 0, and successful transfer, then change the state */
        MSC_Handle->hbot.state  = BOT_RECEIVE_CSW;
      }  
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_URB_EVENT, 0);
#endif       
    }
    
    else if(URB_Status == USBH_URB_NOTREADY)
    {
      /* Re-send same data */      
      MSC_Handle->hbot.state  = BOT_DATA_OUT;
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_URB_EVENT, 0);
#endif       
    }
    
    else if(URB_Status == USBH_URB_STALL)
    {
      MSC_Handle->hbot.state  = BOT_ERROR_OUT;
      
      /* Refer to USB Mass-Storage Class : BOT (www.usb.org) 
      6.7.3 Ho - Host expects to send data to the device
      3. On a STALL condition sending data, then:
      " The host shall clear the Bulk-Out pipe.
      4. The host shall attempt to receive a CSW.
      */      
#if (USBH_USE_OS == 1)
      osMessagePut ( phost->os_event, USBH_URB_EVENT, 0);
#endif       
    }
    break;
    
  case BOT_RECEIVE_CSW:
    
    USBH_BulkReceiveData (phost,
                          MSC_Handle->hbot.csw.data, 
                          BOT_CSW_LENGTH , 
                          MSC_Handle->InPipe);
    
    MSC_Handle->hbot.state  = BOT_RECEIVE_CSW_WAIT;
    break;
    
  case BOT_RECEIVE_CSW_WAIT:
    
    URB_Status = USBH_LL_GetURBState(phost, MSC_Handle->InPipe); 
    
    /* Decode CSW */
    if(URB_Status == USBH_URB_DONE)
    {
      MSC_Handle->hbot.state = BOT_SEND_CBW;    
      MSC_Handle->hbot.cmd_state = BOT_CMD_SEND;        
      CSW_Status = USBH_MSC_DecodeCSW(phost);
      
      if(CSW_Status == BOT_CSW_CMD_PASSED)
      {
        status = USBH_OK;
      }
      else
      {
        status = USBH_FAIL;
      }
#if (USBH_USE_OS == 1)
      osMessagePut ( phost->os_event, USBH_URB_EVENT, 0);
#endif       
    }
    else if(URB_Status == USBH_URB_STALL)     
    {
      MSC_Handle->hbot.state  = BOT_ERROR_IN;
#if (USBH_USE_OS == 1)
      osMessagePut ( phost->os_event, USBH_URB_EVENT, 0);
#endif       
    }
    break;
    
  case BOT_ERROR_IN: 
    error = USBH_MSC_BOT_Abort(phost, lun, BOT_DIR_IN);
    
    if (error == USBH_OK)
    {
      MSC_Handle->hbot.state = BOT_RECEIVE_CSW;
    }
    else if (error == USBH_UNRECOVERED_ERROR)
    {
      /* This means that there is a STALL Error limit, Do Reset Recovery */
      MSC_Handle->hbot.state = BOT_UNRECOVERED_ERROR;
    }
    break;
    
  case BOT_ERROR_OUT: 
    error = USBH_MSC_BOT_Abort(phost, lun, BOT_DIR_OUT);
    
    if ( error == USBH_OK)
    { 
      
      toggle = USBH_LL_GetToggle(phost, MSC_Handle->OutPipe); 
      USBH_LL_SetToggle(phost, MSC_Handle->OutPipe, 1- toggle);   
      USBH_LL_SetToggle(phost, MSC_Handle->InPipe, 0);  
      MSC_Handle->hbot.state = BOT_ERROR_IN;        
    }
    else if (error == USBH_UNRECOVERED_ERROR)
    {
      MSC_Handle->hbot.state = BOT_UNRECOVERED_ERROR;
    }
    break;
    
    
  case BOT_UNRECOVERED_ERROR: 
    status = USBH_MSC_BOT_REQ_Reset(phost);
    if ( status == USBH_OK)
    {
      MSC_Handle->hbot.state = BOT_SEND_CBW; 
    }
    break;
    
  default:      
    break;
  }
  return status;
}