#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int dDataResidue; } ;
struct TYPE_13__ {scalar_t__ scsi_blk_len; int scsi_blk_addr_in_blks; int scsi_blk_size; int /*<<< orphan*/  bot_data; TYPE_2__ csw; TYPE_1__* bdev_ops; } ;
struct TYPE_12__ {TYPE_4__ MSC_BOT_ClassData; } ;
typedef  TYPE_3__ usbd_cdc_msc_hid_state_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int int8_t ;
typedef  TYPE_4__ USBD_MSC_BOT_HandleTypeDef ;
struct TYPE_14__ {scalar_t__ pClassData; } ;
typedef  TYPE_5__ USBD_HandleTypeDef ;
struct TYPE_10__ {scalar_t__ (* Write ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HARDWARE_ERROR ; 
 int MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSC_BOT_SendCSW (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSC_MEDIA_PACKET ; 
 int /*<<< orphan*/  MSC_OUT_EP ; 
 int /*<<< orphan*/  SCSI_SenseCode (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_CSW_CMD_PASSED ; 
 int /*<<< orphan*/  USBD_LL_PrepareReceive (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE_FAULT ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int8_t SCSI_ProcessWrite (USBD_HandleTypeDef  *pdev, uint8_t lun)
{
  uint32_t len;
  USBD_MSC_BOT_HandleTypeDef *hmsc = &((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->MSC_BOT_ClassData;

  len = MIN(hmsc->scsi_blk_len , MSC_MEDIA_PACKET);

  if(hmsc->bdev_ops->Write(lun ,
                              hmsc->bot_data,
                              hmsc->scsi_blk_addr_in_blks,
                              len / hmsc->scsi_blk_size) < 0)
  {
    SCSI_SenseCode(pdev,
                   lun,
                   HARDWARE_ERROR,
                   WRITE_FAULT);
    return -1;
  }


  hmsc->scsi_blk_addr_in_blks += len / hmsc->scsi_blk_size;
  hmsc->scsi_blk_len   -= len;

  /* case 12 : Ho = Do */
  hmsc->csw.dDataResidue -= len;

  if (hmsc->scsi_blk_len == 0)
  {
    MSC_BOT_SendCSW (pdev, USBD_CSW_CMD_PASSED);
  }
  else
  {
    /* Prapare EP to Receive next packet */
    USBD_LL_PrepareReceive (pdev,
                            MSC_OUT_EP,
                            hmsc->bot_data,
                            MIN (hmsc->scsi_blk_len, MSC_MEDIA_PACKET));
  }

  return 0;
}