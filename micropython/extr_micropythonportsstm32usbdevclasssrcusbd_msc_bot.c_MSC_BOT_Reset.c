#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  cbw; int /*<<< orphan*/  bot_status; int /*<<< orphan*/  bot_state; } ;
struct TYPE_6__ {TYPE_2__ MSC_BOT_ClassData; } ;
typedef  TYPE_1__ usbd_cdc_msc_hid_state_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  TYPE_2__ USBD_MSC_BOT_HandleTypeDef ;
struct TYPE_8__ {scalar_t__ pClassData; } ;
typedef  TYPE_3__ USBD_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  MSC_OUT_EP ; 
 int /*<<< orphan*/  USBD_BOT_CBW_LENGTH ; 
 int /*<<< orphan*/  USBD_BOT_IDLE ; 
 int /*<<< orphan*/  USBD_BOT_STATUS_RECOVERY ; 
 int /*<<< orphan*/  USBD_LL_PrepareReceive (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void MSC_BOT_Reset (USBD_HandleTypeDef  *pdev)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = &((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->MSC_BOT_ClassData;

  hmsc->bot_state  = USBD_BOT_IDLE;
  hmsc->bot_status = USBD_BOT_STATUS_RECOVERY;

  /* Prapare EP to Receive First BOT Cmd */
  USBD_LL_PrepareReceive (pdev,
                          MSC_OUT_EP,
                          (uint8_t *)&hmsc->cbw,
                          USBD_BOT_CBW_LENGTH);
}