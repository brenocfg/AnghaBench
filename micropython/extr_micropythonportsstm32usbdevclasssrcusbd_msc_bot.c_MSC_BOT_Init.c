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
struct TYPE_10__ {int /*<<< orphan*/  cbw; TYPE_1__* bdev_ops; scalar_t__ scsi_sense_head; scalar_t__ scsi_sense_tail; int /*<<< orphan*/  bot_status; int /*<<< orphan*/  bot_state; } ;
struct TYPE_9__ {TYPE_3__ MSC_BOT_ClassData; } ;
typedef  TYPE_2__ usbd_cdc_msc_hid_state_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  TYPE_3__ USBD_MSC_BOT_HandleTypeDef ;
struct TYPE_11__ {scalar_t__ pClassData; } ;
typedef  TYPE_4__ USBD_HandleTypeDef ;
struct TYPE_8__ {int /*<<< orphan*/  (* Init ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MSC_IN_EP ; 
 int /*<<< orphan*/  MSC_OUT_EP ; 
 int /*<<< orphan*/  USBD_BOT_CBW_LENGTH ; 
 int /*<<< orphan*/  USBD_BOT_IDLE ; 
 int /*<<< orphan*/  USBD_BOT_STATUS_NORMAL ; 
 int /*<<< orphan*/  USBD_LL_FlushEP (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_LL_PrepareReceive (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void MSC_BOT_Init (USBD_HandleTypeDef  *pdev)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = &((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->MSC_BOT_ClassData;

  hmsc->bot_state  = USBD_BOT_IDLE;
  hmsc->bot_status = USBD_BOT_STATUS_NORMAL;

  hmsc->scsi_sense_tail = 0;
  hmsc->scsi_sense_head = 0;

  hmsc->bdev_ops->Init(0);

  USBD_LL_FlushEP(pdev, MSC_OUT_EP);
  USBD_LL_FlushEP(pdev, MSC_IN_EP);

  /* Prapare EP to Receive First BOT Cmd */
  USBD_LL_PrepareReceive (pdev,
                          MSC_OUT_EP,
                          (uint8_t *)&hmsc->cbw,
                          USBD_BOT_CBW_LENGTH);
}