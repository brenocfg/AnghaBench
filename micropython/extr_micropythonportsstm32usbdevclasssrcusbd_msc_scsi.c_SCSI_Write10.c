#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int bmFlags; int bLUN; int dDataLength; } ;
struct TYPE_14__ {scalar_t__ bot_state; int scsi_blk_addr_in_blks; int scsi_blk_len; int scsi_blk_size; int /*<<< orphan*/  bot_data; TYPE_2__ cbw; TYPE_1__* bdev_ops; } ;
struct TYPE_13__ {TYPE_4__ MSC_BOT_ClassData; } ;
typedef  TYPE_3__ usbd_cdc_msc_hid_state_t ;
typedef  int uint8_t ;
typedef  int int8_t ;
typedef  TYPE_4__ USBD_MSC_BOT_HandleTypeDef ;
struct TYPE_15__ {scalar_t__ pClassData; } ;
typedef  TYPE_5__ USBD_HandleTypeDef ;
struct TYPE_11__ {scalar_t__ (* IsReady ) (int) ;scalar_t__ (* IsWriteProtected ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  INVALID_CDB ; 
 int /*<<< orphan*/  MEDIUM_NOT_PRESENT ; 
 int /*<<< orphan*/  MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSC_MEDIA_PACKET ; 
 int /*<<< orphan*/  MSC_OUT_EP ; 
 int /*<<< orphan*/  NOT_READY ; 
 scalar_t__ SCSI_CheckAddressRange (TYPE_5__*,int,int,int) ; 
 int SCSI_ProcessWrite (TYPE_5__*,int) ; 
 int /*<<< orphan*/  SCSI_SenseCode (TYPE_5__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ USBD_BOT_DATA_OUT ; 
 scalar_t__ USBD_BOT_IDLE ; 
 int /*<<< orphan*/  USBD_LL_PrepareReceive (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_PROTECTED ; 
 scalar_t__ stub1 (int) ; 
 scalar_t__ stub2 (int) ; 

__attribute__((used)) static int8_t SCSI_Write10 (USBD_HandleTypeDef  *pdev, uint8_t lun , uint8_t *params)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = &((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->MSC_BOT_ClassData;

  if (hmsc->bot_state == USBD_BOT_IDLE) /* Idle */
  {

    /* case 8 : Hi <> Do */

    if ((hmsc->cbw.bmFlags & 0x80) == 0x80)
    {
      SCSI_SenseCode(pdev,
                     hmsc->cbw.bLUN,
                     ILLEGAL_REQUEST,
                     INVALID_CDB);
      return -1;
    }

    /* Check whether Media is ready */
    if(hmsc->bdev_ops->IsReady(lun) !=0 )
    {
      SCSI_SenseCode(pdev,
                     lun,
                     NOT_READY,
                     MEDIUM_NOT_PRESENT);
      return -1;
    }

    /* Check If media is write-protected */
    if(hmsc->bdev_ops->IsWriteProtected(lun) !=0 )
    {
      SCSI_SenseCode(pdev,
                     lun,
                     NOT_READY,
                     WRITE_PROTECTED);
      return -1;
    }


    hmsc->scsi_blk_addr_in_blks = (params[2] << 24) | \
      (params[3] << 16) | \
        (params[4] <<  8) | \
          params[5];
    hmsc->scsi_blk_len = (params[7] <<  8) | \
      params[8];

    /* check if LBA address is in the right range */
    if(SCSI_CheckAddressRange(pdev,
                              lun,
                              hmsc->scsi_blk_addr_in_blks,
                              hmsc->scsi_blk_len) < 0)
    {
      return -1; /* error */
    }

    hmsc->scsi_blk_len  *= hmsc->scsi_blk_size;

    /* cases 3,11,13 : Hn,Ho <> D0 */
    if (hmsc->cbw.dDataLength != hmsc->scsi_blk_len)
    {
      SCSI_SenseCode(pdev,
                     hmsc->cbw.bLUN,
                     ILLEGAL_REQUEST,
                     INVALID_CDB);
      return -1;
    }

    /* Prepare EP to receive first data packet */
    hmsc->bot_state = USBD_BOT_DATA_OUT;
    USBD_LL_PrepareReceive (pdev,
                      MSC_OUT_EP,
                      hmsc->bot_data,
                      MIN (hmsc->scsi_blk_len, MSC_MEDIA_PACKET));
  }
  else /* Write Process ongoing */
  {
    return SCSI_ProcessWrite(pdev, lun);
  }
  return 0;
}