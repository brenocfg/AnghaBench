#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USBH_URBStateTypeDef ;
struct TYPE_11__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_3__ USBH_HandleTypeDef ;
struct TYPE_10__ {int /*<<< orphan*/  OutEpSize; int /*<<< orphan*/  OutPipe; } ;
struct TYPE_12__ {int data_tx_state; int /*<<< orphan*/  TxDataLength; TYPE_2__ DataItf; int /*<<< orphan*/  pTxData; } ;
struct TYPE_9__ {TYPE_4__* pData; } ;
typedef  TYPE_4__ CDC_HandleTypeDef ;

/* Variables and functions */
 int CDC_IDLE ; 
#define  CDC_SEND_DATA 129 
#define  CDC_SEND_DATA_WAIT 128 
 int /*<<< orphan*/  USBH_BulkSendData (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USBH_CDC_TransmitCallback (TYPE_3__*) ; 
 int /*<<< orphan*/  USBH_LL_GetURBState (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_URB_DONE ; 
 int /*<<< orphan*/  USBH_URB_IDLE ; 
 int /*<<< orphan*/  USBH_URB_NOTREADY ; 

__attribute__((used)) static void CDC_ProcessTransmission(USBH_HandleTypeDef *phost)
{
  CDC_HandleTypeDef *CDC_Handle =  phost->pActiveClass->pData;
  USBH_URBStateTypeDef URB_Status = USBH_URB_IDLE;
  
  switch(CDC_Handle->data_tx_state)
  {
 
  case CDC_SEND_DATA:
    if(CDC_Handle->TxDataLength > CDC_Handle->DataItf.OutEpSize)
    {
      USBH_BulkSendData (phost,
                         CDC_Handle->pTxData, 
                         CDC_Handle->DataItf.OutEpSize, 
                         CDC_Handle->DataItf.OutPipe,
                         1);
    }
    else
    {
      USBH_BulkSendData (phost,
                         CDC_Handle->pTxData, 
                         CDC_Handle->TxDataLength, 
                         CDC_Handle->DataItf.OutPipe,
                         1);
    }
    
    CDC_Handle->data_tx_state = CDC_SEND_DATA_WAIT;
    
    break;
    
  case CDC_SEND_DATA_WAIT:
    
    URB_Status = USBH_LL_GetURBState(phost, CDC_Handle->DataItf.OutPipe); 
    
    /*Check the status done for transmssion*/
    if(URB_Status == USBH_URB_DONE )
    {         
      if(CDC_Handle->TxDataLength > CDC_Handle->DataItf.OutEpSize)
      {
        CDC_Handle->TxDataLength -= CDC_Handle->DataItf.OutEpSize ;
        CDC_Handle->pTxData += CDC_Handle->DataItf.OutEpSize;
      }
      else
      {
        CDC_Handle->TxDataLength = 0;
      }
      
      if( CDC_Handle->TxDataLength > 0)
      {
       CDC_Handle->data_tx_state = CDC_SEND_DATA; 
      }
      else
      {
        CDC_Handle->data_tx_state = CDC_IDLE;    
        USBH_CDC_TransmitCallback(phost);

      }
    }
    else if( URB_Status == USBH_URB_NOTREADY )
    {
      CDC_Handle->data_tx_state = CDC_SEND_DATA; 
    }
    break;
  default:
    break;
  }
}