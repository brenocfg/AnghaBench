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
struct TYPE_9__ {scalar_t__ dDataLength; int /*<<< orphan*/  bLUN; } ;
struct TYPE_11__ {scalar_t__ bot_data_length; int /*<<< orphan*/  bot_state; TYPE_1__* bdev_ops; TYPE_2__ cbw; } ;
struct TYPE_10__ {TYPE_4__ MSC_BOT_ClassData; } ;
typedef  TYPE_3__ usbd_cdc_msc_hid_state_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int8_t ;
typedef  TYPE_4__ USBD_MSC_BOT_HandleTypeDef ;
struct TYPE_12__ {scalar_t__ pClassData; } ;
typedef  TYPE_5__ USBD_HandleTypeDef ;
struct TYPE_8__ {scalar_t__ (* IsReady ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  INVALID_CDB ; 
 int /*<<< orphan*/  MEDIUM_NOT_PRESENT ; 
 int /*<<< orphan*/  NOT_READY ; 
 int /*<<< orphan*/  SCSI_SenseCode (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_BOT_NO_DATA ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int8_t SCSI_TestUnitReady(USBD_HandleTypeDef  *pdev, uint8_t lun, uint8_t *params)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = &((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->MSC_BOT_ClassData;

  /* case 9 : Hi > D0 */
  if (hmsc->cbw.dDataLength != 0)
  {
    SCSI_SenseCode(pdev,
                   hmsc->cbw.bLUN,
                   ILLEGAL_REQUEST,
                   INVALID_CDB);
    return -1;
  }

  if(hmsc->bdev_ops->IsReady(lun) !=0 )
  {
    SCSI_SenseCode(pdev,
                   lun,
                   NOT_READY,
                   MEDIUM_NOT_PRESENT);

    hmsc->bot_state = USBD_BOT_NO_DATA;
    return -1;
  }
  hmsc->bot_data_length = 0;
  return 0;
}