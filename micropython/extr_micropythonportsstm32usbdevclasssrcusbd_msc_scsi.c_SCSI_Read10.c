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
struct TYPE_11__ {int bmFlags; int bLUN; int dDataLength; } ;
struct TYPE_13__ {scalar_t__ bot_state; int scsi_blk_addr_in_blks; int scsi_blk_len; int scsi_blk_size; int /*<<< orphan*/  bot_data_length; TYPE_2__ cbw; TYPE_1__* bdev_ops; } ;
struct TYPE_12__ {TYPE_4__ MSC_BOT_ClassData; } ;
typedef  TYPE_3__ usbd_cdc_msc_hid_state_t ;
typedef  int uint8_t ;
typedef  int int8_t ;
typedef  TYPE_4__ USBD_MSC_BOT_HandleTypeDef ;
struct TYPE_14__ {scalar_t__ pClassData; } ;
typedef  TYPE_5__ USBD_HandleTypeDef ;
struct TYPE_10__ {scalar_t__ (* IsReady ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  INVALID_CDB ; 
 int /*<<< orphan*/  MEDIUM_NOT_PRESENT ; 
 int /*<<< orphan*/  MSC_MEDIA_PACKET ; 
 int /*<<< orphan*/  NOT_READY ; 
 scalar_t__ SCSI_CheckAddressRange (TYPE_5__*,int,int,int) ; 
 int SCSI_ProcessRead (TYPE_5__*,int) ; 
 int /*<<< orphan*/  SCSI_SenseCode (TYPE_5__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ USBD_BOT_DATA_IN ; 
 scalar_t__ USBD_BOT_IDLE ; 
 scalar_t__ stub1 (int) ; 

__attribute__((used)) static int8_t SCSI_Read10(USBD_HandleTypeDef  *pdev, uint8_t lun , uint8_t *params)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = &((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->MSC_BOT_ClassData;

  if(hmsc->bot_state == USBD_BOT_IDLE)  /* Idle */
  {

    /* case 10 : Ho <> Di */

    if ((hmsc->cbw.bmFlags & 0x80) != 0x80)
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
      return -1;
    }

    hmsc->scsi_blk_addr_in_blks = (params[2] << 24) | \
      (params[3] << 16) | \
        (params[4] <<  8) | \
          params[5];

    hmsc->scsi_blk_len =  (params[7] <<  8) | \
      params[8];



    if( SCSI_CheckAddressRange(pdev, lun, hmsc->scsi_blk_addr_in_blks, hmsc->scsi_blk_len) < 0)
    {
      return -1; /* error */
    }

    hmsc->bot_state = USBD_BOT_DATA_IN;
    hmsc->scsi_blk_len  *= hmsc->scsi_blk_size;

    /* cases 4,5 : Hi <> Dn */
    if (hmsc->cbw.dDataLength != hmsc->scsi_blk_len)
    {
      SCSI_SenseCode(pdev,
                     hmsc->cbw.bLUN,
                     ILLEGAL_REQUEST,
                     INVALID_CDB);
      return -1;
    }
  }
  hmsc->bot_data_length = MSC_MEDIA_PACKET;

  return SCSI_ProcessRead(pdev, lun);
}