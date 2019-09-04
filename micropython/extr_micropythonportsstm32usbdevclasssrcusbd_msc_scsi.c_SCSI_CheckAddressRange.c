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
struct TYPE_7__ {scalar_t__ scsi_blk_nbr; } ;
struct TYPE_6__ {TYPE_2__ MSC_BOT_ClassData; } ;
typedef  TYPE_1__ usbd_cdc_msc_hid_state_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int int8_t ;
typedef  TYPE_2__ USBD_MSC_BOT_HandleTypeDef ;
struct TYPE_8__ {scalar_t__ pClassData; } ;
typedef  TYPE_3__ USBD_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRESS_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  SCSI_SenseCode (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int8_t SCSI_CheckAddressRange (USBD_HandleTypeDef  *pdev, uint8_t lun , uint32_t blk_offset , uint16_t blk_nbr)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = &((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->MSC_BOT_ClassData;

  if ((blk_offset + blk_nbr) > hmsc->scsi_blk_nbr )
  {
    SCSI_SenseCode(pdev,
                   lun,
                   ILLEGAL_REQUEST,
                   ADDRESS_OUT_OF_RANGE);
    return -1;
  }
  return 0;
}