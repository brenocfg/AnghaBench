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
struct TYPE_8__ {int scsi_blk_addr_in_blks; int scsi_blk_len; scalar_t__ bot_data_length; } ;
struct TYPE_7__ {TYPE_2__ MSC_BOT_ClassData; } ;
typedef  TYPE_1__ usbd_cdc_msc_hid_state_t ;
typedef  int uint8_t ;
typedef  int int8_t ;
typedef  TYPE_2__ USBD_MSC_BOT_HandleTypeDef ;
struct TYPE_9__ {scalar_t__ pClassData; } ;
typedef  TYPE_3__ USBD_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  INVALID_FIELED_IN_COMMAND ; 
 scalar_t__ SCSI_CheckAddressRange (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  SCSI_SenseCode (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int8_t SCSI_Verify10(USBD_HandleTypeDef  *pdev, uint8_t lun , uint8_t *params)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = &((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->MSC_BOT_ClassData;

  if ((params[1]& 0x02) == 0x02)
  {
    SCSI_SenseCode (pdev,
                    lun,
                    ILLEGAL_REQUEST,
                    INVALID_FIELED_IN_COMMAND);
    return -1; /* Error, Verify Mode Not supported*/
  }

  hmsc->scsi_blk_addr_in_blks = (params[2] << 24) | (params[3] << 16) | (params[4] << 8) | params[5];
  hmsc->scsi_blk_len = (params[7] << 8) | params[8];

  if(SCSI_CheckAddressRange(pdev,
                            lun,
                            hmsc->scsi_blk_addr_in_blks,
                            hmsc->scsi_blk_len) < 0)
  {
    return -1; /* error */
  }
  hmsc->bot_data_length = 0;
  return 0;
}