#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  bStatus; int /*<<< orphan*/  dDataResidue; } ;
struct TYPE_8__ {int /*<<< orphan*/  dDataLength; } ;
struct TYPE_11__ {int /*<<< orphan*/  bot_state; TYPE_2__ csw; TYPE_1__ cbw; } ;
struct TYPE_10__ {TYPE_4__ MSC_BOT_ClassData; } ;
typedef  TYPE_3__ usbd_cdc_msc_hid_state_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  TYPE_4__ USBD_MSC_BOT_HandleTypeDef ;
struct TYPE_12__ {scalar_t__ pClassData; } ;
typedef  TYPE_5__ USBD_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSC_IN_EP ; 
 int /*<<< orphan*/  USBD_BOT_SEND_DATA ; 
 int /*<<< orphan*/  USBD_CSW_CMD_PASSED ; 
 int /*<<< orphan*/  USBD_LL_Transmit (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void  MSC_BOT_SendData(USBD_HandleTypeDef  *pdev,
                              uint8_t* buf,
                              uint16_t len)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = &((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->MSC_BOT_ClassData;

  len = MIN (hmsc->cbw.dDataLength, len);
  hmsc->csw.dDataResidue -= len;
  hmsc->csw.bStatus = USBD_CSW_CMD_PASSED;
  hmsc->bot_state = USBD_BOT_SEND_DATA;

  USBD_LL_Transmit (pdev, MSC_IN_EP, buf, len);
}