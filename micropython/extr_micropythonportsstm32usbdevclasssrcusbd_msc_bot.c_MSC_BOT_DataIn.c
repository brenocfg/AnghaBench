#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * CB; int /*<<< orphan*/  bLUN; } ;
struct TYPE_10__ {int bot_state; TYPE_1__ cbw; } ;
struct TYPE_9__ {TYPE_3__ MSC_BOT_ClassData; } ;
typedef  TYPE_2__ usbd_cdc_msc_hid_state_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  TYPE_3__ USBD_MSC_BOT_HandleTypeDef ;
struct TYPE_11__ {scalar_t__ pClassData; } ;
typedef  TYPE_4__ USBD_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  MSC_BOT_SendCSW (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCSI_ProcessCmd (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  USBD_BOT_DATA_IN 130 
#define  USBD_BOT_LAST_DATA_IN 129 
#define  USBD_BOT_SEND_DATA 128 
 int /*<<< orphan*/  USBD_CSW_CMD_FAILED ; 
 int /*<<< orphan*/  USBD_CSW_CMD_PASSED ; 

void MSC_BOT_DataIn (USBD_HandleTypeDef  *pdev,
                     uint8_t epnum)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = &((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->MSC_BOT_ClassData;

  switch (hmsc->bot_state)
  {
  case USBD_BOT_DATA_IN:
    if(SCSI_ProcessCmd(pdev,
                        hmsc->cbw.bLUN,
                        &hmsc->cbw.CB[0]) < 0)
    {
      MSC_BOT_SendCSW (pdev, USBD_CSW_CMD_FAILED);
    }
    break;

  case USBD_BOT_SEND_DATA:
  case USBD_BOT_LAST_DATA_IN:
    MSC_BOT_SendCSW (pdev, USBD_CSW_CMD_PASSED);

    break;

  default:
    break;
  }
}