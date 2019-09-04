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
struct TYPE_8__ {int /*<<< orphan*/  bStatus; int /*<<< orphan*/  dSignature; } ;
struct TYPE_10__ {int /*<<< orphan*/  cbw; TYPE_1__ csw; int /*<<< orphan*/  bot_state; } ;
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
 int /*<<< orphan*/  USBD_BOT_CSW_LENGTH ; 
 int /*<<< orphan*/  USBD_BOT_CSW_SIGNATURE ; 
 int /*<<< orphan*/  USBD_BOT_IDLE ; 
 int /*<<< orphan*/  USBD_LL_PrepareReceive (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_LL_Transmit (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void  MSC_BOT_SendCSW (USBD_HandleTypeDef  *pdev,
                              uint8_t CSW_Status)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = &((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->MSC_BOT_ClassData;

  hmsc->csw.dSignature = USBD_BOT_CSW_SIGNATURE;
  hmsc->csw.bStatus = CSW_Status;
  hmsc->bot_state = USBD_BOT_IDLE;

  USBD_LL_Transmit (pdev,
             MSC_IN_EP,
             (uint8_t *)&hmsc->csw,
             USBD_BOT_CSW_LENGTH);

  /* Prapare EP to Receive next Cmd */
  USBD_LL_PrepareReceive (pdev,
                    MSC_OUT_EP,
                    (uint8_t *)&hmsc->cbw,
                    USBD_BOT_CBW_LENGTH);

}