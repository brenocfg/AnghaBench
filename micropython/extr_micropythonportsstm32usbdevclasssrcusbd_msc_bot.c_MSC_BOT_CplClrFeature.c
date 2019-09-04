#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ bot_status; } ;
struct TYPE_7__ {TYPE_2__ MSC_BOT_ClassData; } ;
typedef  TYPE_1__ usbd_cdc_msc_hid_state_t ;
typedef  int uint8_t ;
typedef  TYPE_2__ USBD_MSC_BOT_HandleTypeDef ;
struct TYPE_9__ {scalar_t__ pClassData; } ;
typedef  TYPE_3__ USBD_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  MSC_BOT_SendCSW (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSC_IN_EP ; 
 scalar_t__ USBD_BOT_STATUS_ERROR ; 
 scalar_t__ USBD_BOT_STATUS_NORMAL ; 
 scalar_t__ USBD_BOT_STATUS_RECOVERY ; 
 int /*<<< orphan*/  USBD_CSW_CMD_FAILED ; 
 int /*<<< orphan*/  USBD_LL_StallEP (TYPE_3__*,int /*<<< orphan*/ ) ; 

void  MSC_BOT_CplClrFeature (USBD_HandleTypeDef  *pdev, uint8_t epnum)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = &((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->MSC_BOT_ClassData;

  if(hmsc->bot_status == USBD_BOT_STATUS_ERROR )/* Bad CBW Signature */
  {
    USBD_LL_StallEP(pdev, MSC_IN_EP);
    hmsc->bot_status = USBD_BOT_STATUS_NORMAL;
  }
  else if(((epnum & 0x80) == 0x80) && ( hmsc->bot_status != USBD_BOT_STATUS_RECOVERY))
  {
    MSC_BOT_SendCSW (pdev, USBD_CSW_CMD_FAILED);
  }

}