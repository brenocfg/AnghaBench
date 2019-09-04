#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int dDataResidue; } ;
struct TYPE_12__ {scalar_t__ scsi_blk_len; int scsi_blk_addr_in_blks; int scsi_blk_size; int /*<<< orphan*/  bot_state; TYPE_2__ csw; int /*<<< orphan*/  bot_data; TYPE_1__* bdev_ops; } ;
struct TYPE_11__ {TYPE_4__ MSC_BOT_ClassData; } ;
typedef  TYPE_3__ usbd_cdc_msc_hid_state_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int int8_t ;
typedef  TYPE_4__ USBD_MSC_BOT_HandleTypeDef ;
struct TYPE_13__ {scalar_t__ pClassData; } ;
typedef  TYPE_5__ USBD_HandleTypeDef ;
struct TYPE_9__ {scalar_t__ (* Read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HARDWARE_ERROR ; 
 int MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSC_IN_EP ; 
 int /*<<< orphan*/  MSC_MEDIA_PACKET ; 
 int /*<<< orphan*/  SCSI_SenseCode (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNRECOVERED_READ_ERROR ; 
 int /*<<< orphan*/  USBD_BOT_LAST_DATA_IN ; 
 int /*<<< orphan*/  USBD_LL_Transmit (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int8_t SCSI_ProcessRead (USBD_HandleTypeDef  *pdev, uint8_t lun)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = &((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->MSC_BOT_ClassData;
  uint32_t len;

  len = MIN(hmsc->scsi_blk_len , MSC_MEDIA_PACKET);

  if( hmsc->bdev_ops->Read(lun ,
                              hmsc->bot_data,
                              hmsc->scsi_blk_addr_in_blks,
                              len / hmsc->scsi_blk_size) < 0)
  {

    SCSI_SenseCode(pdev,
                   lun,
                   HARDWARE_ERROR,
                   UNRECOVERED_READ_ERROR);
    return -1;
  }


  USBD_LL_Transmit (pdev,
             MSC_IN_EP,
             hmsc->bot_data,
             len);


  hmsc->scsi_blk_addr_in_blks += len / hmsc->scsi_blk_size;
  hmsc->scsi_blk_len    -= len;

  /* case 6 : Hi = Di */
  hmsc->csw.dDataResidue -= len;

  if (hmsc->scsi_blk_len == 0)
  {
    hmsc->bot_state = USBD_BOT_LAST_DATA_IN;
  }
  return 0;
}