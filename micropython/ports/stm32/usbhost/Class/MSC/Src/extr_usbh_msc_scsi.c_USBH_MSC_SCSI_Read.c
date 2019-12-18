#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_13__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_5__ USBH_HandleTypeDef ;
struct TYPE_10__ {int DataTransferLength; void** CB; int /*<<< orphan*/  CBLength; int /*<<< orphan*/  Flags; } ;
struct TYPE_11__ {TYPE_2__ field; } ;
struct TYPE_12__ {int cmd_state; void** pbuf; int /*<<< orphan*/  state; TYPE_3__ cbw; } ;
struct TYPE_14__ {TYPE_4__ hbot; } ;
struct TYPE_9__ {TYPE_6__* pData; } ;
typedef  TYPE_6__ MSC_HandleTypeDef ;

/* Variables and functions */
#define  BOT_CMD_SEND 129 
#define  BOT_CMD_WAIT 128 
 int /*<<< orphan*/  BOT_SEND_CBW ; 
 int /*<<< orphan*/  CBW_CB_LENGTH ; 
 int /*<<< orphan*/  CBW_LENGTH ; 
 void* OPCODE_READ10 ; 
 int /*<<< orphan*/  USBH_BUSY ; 
 int /*<<< orphan*/  USBH_FAIL ; 
 int /*<<< orphan*/  USBH_MSC_BOT_Process (TYPE_5__*,void*) ; 
 int /*<<< orphan*/  USBH_memset (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_EP_DIR_IN ; 

USBH_StatusTypeDef USBH_MSC_SCSI_Read(USBH_HandleTypeDef *phost,
                                     uint8_t lun,
                                     uint32_t address,
                                     uint8_t *pbuf,
                                     uint32_t length)
{
  USBH_StatusTypeDef    error = USBH_FAIL ;
  MSC_HandleTypeDef *MSC_Handle =  phost->pActiveClass->pData;
  
  switch(MSC_Handle->hbot.cmd_state)
  {
  case BOT_CMD_SEND:  
    
    /*Prepare the CBW and relevent field*/
    MSC_Handle->hbot.cbw.field.DataTransferLength = length * 512;
    MSC_Handle->hbot.cbw.field.Flags = USB_EP_DIR_IN;
    MSC_Handle->hbot.cbw.field.CBLength = CBW_LENGTH;
    
    USBH_memset(MSC_Handle->hbot.cbw.field.CB, 0, CBW_CB_LENGTH);
    MSC_Handle->hbot.cbw.field.CB[0]  = OPCODE_READ10; 
    
    /*logical block address*/
    MSC_Handle->hbot.cbw.field.CB[2]  = (((uint8_t*)&address)[3]);
    MSC_Handle->hbot.cbw.field.CB[3]  = (((uint8_t*)&address)[2]);
    MSC_Handle->hbot.cbw.field.CB[4]  = (((uint8_t*)&address)[1]);
    MSC_Handle->hbot.cbw.field.CB[5]  = (((uint8_t*)&address)[0]);
    
    
    /*Tranfer length */
    MSC_Handle->hbot.cbw.field.CB[7]  = (((uint8_t *)&length)[1]) ; 
    MSC_Handle->hbot.cbw.field.CB[8]  = (((uint8_t *)&length)[0]) ; 

    
    MSC_Handle->hbot.state = BOT_SEND_CBW;
    MSC_Handle->hbot.cmd_state = BOT_CMD_WAIT;
    MSC_Handle->hbot.pbuf = pbuf;
    error = USBH_BUSY; 
    break;
    
  case BOT_CMD_WAIT: 
    error = USBH_MSC_BOT_Process(phost, lun);
    break;
    
  default:
    break;
  }
  
  return error;
}