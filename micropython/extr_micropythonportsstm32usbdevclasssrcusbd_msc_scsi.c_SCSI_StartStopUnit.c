#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* bdev_ops; scalar_t__ bot_data_length; } ;
struct TYPE_7__ {TYPE_3__ MSC_BOT_ClassData; } ;
typedef  TYPE_2__ usbd_cdc_msc_hid_state_t ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  TYPE_3__ USBD_MSC_BOT_HandleTypeDef ;
struct TYPE_9__ {scalar_t__ pClassData; } ;
typedef  TYPE_4__ USBD_HandleTypeDef ;
struct TYPE_6__ {int /*<<< orphan*/  (* StartStopUnit ) (int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int,int) ; 

__attribute__((used)) static int8_t SCSI_StartStopUnit(USBD_HandleTypeDef  *pdev, uint8_t lun, uint8_t *params)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = &((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->MSC_BOT_ClassData;
  hmsc->bot_data_length = 0;

  // On Mac OS X, when the device is ejected a SCSI_START_STOP_UNIT command is sent.
  // Bit 0 of params[4] is the START bit.
  // If we get a stop, we must really stop the device so that the Mac does not
  // automatically remount it.
  hmsc->bdev_ops->StartStopUnit(lun, params[4] & 1);

  return 0;
}