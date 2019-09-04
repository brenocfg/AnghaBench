#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int* bot_data; int bot_data_length; TYPE_1__* bdev_ops; } ;
struct TYPE_8__ {TYPE_3__ MSC_BOT_ClassData; } ;
typedef  TYPE_2__ usbd_cdc_msc_hid_state_t ;
typedef  void* uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int int8_t ;
typedef  TYPE_3__ USBD_MSC_BOT_HandleTypeDef ;
struct TYPE_10__ {scalar_t__ pClassData; } ;
typedef  TYPE_4__ USBD_HandleTypeDef ;
struct TYPE_7__ {scalar_t__ (* GetCapacity ) (void*,int*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIUM_NOT_PRESENT ; 
 int /*<<< orphan*/  NOT_READY ; 
 int /*<<< orphan*/  SCSI_SenseCode (TYPE_4__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (void*,int*,int*) ; 

__attribute__((used)) static int8_t SCSI_ReadFormatCapacity(USBD_HandleTypeDef  *pdev, uint8_t lun, uint8_t *params)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = &((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->MSC_BOT_ClassData;

  uint16_t blk_size;
  uint32_t blk_nbr;
  uint16_t i;

  for(i=0 ; i < 12 ; i++)
  {
    hmsc->bot_data[i] = 0;
  }

  if(hmsc->bdev_ops->GetCapacity(lun, &blk_nbr, &blk_size) != 0)
  {
    SCSI_SenseCode(pdev,
                   lun,
                   NOT_READY,
                   MEDIUM_NOT_PRESENT);
    return -1;
  }
  else
  {
    hmsc->bot_data[3] = 0x08;
    hmsc->bot_data[4] = (uint8_t)((blk_nbr - 1) >> 24);
    hmsc->bot_data[5] = (uint8_t)((blk_nbr - 1) >> 16);
    hmsc->bot_data[6] = (uint8_t)((blk_nbr - 1) >>  8);
    hmsc->bot_data[7] = (uint8_t)(blk_nbr - 1);

    hmsc->bot_data[8] = 0x02;
    hmsc->bot_data[9] = (uint8_t)(blk_size >>  16);
    hmsc->bot_data[10] = (uint8_t)(blk_size >>  8);
    hmsc->bot_data[11] = (uint8_t)(blk_size);

    hmsc->bot_data_length = 12;
    return 0;
  }
}