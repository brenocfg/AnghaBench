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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_13__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_5__ USBH_HandleTypeDef ;
struct TYPE_10__ {int /*<<< orphan*/ * CB; int /*<<< orphan*/  CBLength; int /*<<< orphan*/  Flags; int /*<<< orphan*/  DataTransferLength; } ;
struct TYPE_11__ {TYPE_2__ field; } ;
struct TYPE_12__ {int cmd_state; int /*<<< orphan*/  state; TYPE_3__ cbw; } ;
struct TYPE_14__ {TYPE_4__ hbot; } ;
struct TYPE_9__ {TYPE_6__* pData; } ;
typedef  TYPE_6__ MSC_HandleTypeDef ;

/* Variables and functions */
#define  BOT_CMD_SEND 129 
#define  BOT_CMD_WAIT 128 
 int /*<<< orphan*/  BOT_SEND_CBW ; 
 int /*<<< orphan*/  CBW_CB_LENGTH ; 
 int /*<<< orphan*/  CBW_LENGTH ; 
 int /*<<< orphan*/  DATA_LEN_MODE_TEST_UNIT_READY ; 
 int /*<<< orphan*/  OPCODE_TEST_UNIT_READY ; 
 int /*<<< orphan*/  USBH_BUSY ; 
 int /*<<< orphan*/  USBH_FAIL ; 
 int /*<<< orphan*/  USBH_MSC_BOT_Process (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_EP_DIR_OUT ; 

USBH_StatusTypeDef USBH_MSC_SCSI_TestUnitReady (USBH_HandleTypeDef *phost, 
                                                uint8_t lun)
{
  USBH_StatusTypeDef    error = USBH_FAIL ;
  MSC_HandleTypeDef *MSC_Handle =  phost->pActiveClass->pData;
  
  switch(MSC_Handle->hbot.cmd_state)
  {
  case BOT_CMD_SEND:  
    
    /*Prepare the CBW and relevent field*/
    MSC_Handle->hbot.cbw.field.DataTransferLength = DATA_LEN_MODE_TEST_UNIT_READY;     
    MSC_Handle->hbot.cbw.field.Flags = USB_EP_DIR_OUT;
    MSC_Handle->hbot.cbw.field.CBLength = CBW_LENGTH;
    
    USBH_memset(MSC_Handle->hbot.cbw.field.CB, 0, CBW_CB_LENGTH);
    MSC_Handle->hbot.cbw.field.CB[0]  = OPCODE_TEST_UNIT_READY; 
    
    MSC_Handle->hbot.state = BOT_SEND_CBW;
    MSC_Handle->hbot.cmd_state = BOT_CMD_WAIT;
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