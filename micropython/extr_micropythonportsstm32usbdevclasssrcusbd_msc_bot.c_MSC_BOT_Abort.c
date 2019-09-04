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
struct TYPE_8__ {scalar_t__ bmFlags; scalar_t__ dDataLength; } ;
struct TYPE_10__ {scalar_t__ bot_status; TYPE_1__ cbw; } ;
struct TYPE_9__ {TYPE_3__ MSC_BOT_ClassData; } ;
typedef  TYPE_2__ usbd_cdc_msc_hid_state_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  TYPE_3__ USBD_MSC_BOT_HandleTypeDef ;
struct TYPE_11__ {scalar_t__ pClassData; } ;
typedef  TYPE_4__ USBD_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  MSC_IN_EP ; 
 int /*<<< orphan*/  MSC_OUT_EP ; 
 int /*<<< orphan*/  USBD_BOT_CBW_LENGTH ; 
 scalar_t__ USBD_BOT_STATUS_ERROR ; 
 scalar_t__ USBD_BOT_STATUS_NORMAL ; 
 int /*<<< orphan*/  USBD_LL_PrepareReceive (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_LL_StallEP (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void  MSC_BOT_Abort (USBD_HandleTypeDef  *pdev)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = &((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->MSC_BOT_ClassData;

  if ((hmsc->cbw.bmFlags == 0) &&
      (hmsc->cbw.dDataLength != 0) &&
      (hmsc->bot_status == USBD_BOT_STATUS_NORMAL) )
  {
    USBD_LL_StallEP(pdev, MSC_OUT_EP );
  }
  USBD_LL_StallEP(pdev, MSC_IN_EP);

  if(hmsc->bot_status == USBD_BOT_STATUS_ERROR)
  {
    USBD_LL_PrepareReceive (pdev,
                      MSC_OUT_EP,
                      (uint8_t *)&hmsc->cbw,
                      USBD_BOT_CBW_LENGTH);
  }
}