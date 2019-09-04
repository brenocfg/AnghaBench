#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int* bot_data; size_t scsi_sense_head; size_t scsi_sense_tail; size_t bot_data_length; TYPE_3__* scsi_sense; } ;
struct TYPE_11__ {TYPE_5__ MSC_BOT_ClassData; } ;
typedef  TYPE_4__ usbd_cdc_msc_hid_state_t ;
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  TYPE_5__ USBD_MSC_BOT_HandleTypeDef ;
struct TYPE_13__ {scalar_t__ pClassData; } ;
typedef  TYPE_6__ USBD_HandleTypeDef ;
struct TYPE_8__ {size_t ASCQ; size_t ASC; } ;
struct TYPE_9__ {TYPE_1__ b; } ;
struct TYPE_10__ {size_t Skey; TYPE_2__ w; } ;

/* Variables and functions */
 size_t REQUEST_SENSE_DATA_LEN ; 
 size_t SENSE_LIST_DEEPTH ; 

__attribute__((used)) static int8_t SCSI_RequestSense (USBD_HandleTypeDef  *pdev, uint8_t lun, uint8_t *params)
{
  uint8_t i;
  USBD_MSC_BOT_HandleTypeDef *hmsc = &((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->MSC_BOT_ClassData;

  for(i=0 ; i < REQUEST_SENSE_DATA_LEN ; i++)
  {
    hmsc->bot_data[i] = 0;
  }

  hmsc->bot_data[0]     = 0x70;
  hmsc->bot_data[7]     = REQUEST_SENSE_DATA_LEN - 6;

  if((hmsc->scsi_sense_head != hmsc->scsi_sense_tail)) {

    hmsc->bot_data[2]     = hmsc->scsi_sense[hmsc->scsi_sense_head].Skey;
    hmsc->bot_data[12]    = hmsc->scsi_sense[hmsc->scsi_sense_head].w.b.ASCQ;
    hmsc->bot_data[13]    = hmsc->scsi_sense[hmsc->scsi_sense_head].w.b.ASC;
    hmsc->scsi_sense_head++;

    if (hmsc->scsi_sense_head == SENSE_LIST_DEEPTH)
    {
      hmsc->scsi_sense_head = 0;
    }
  }
  hmsc->bot_data_length = REQUEST_SENSE_DATA_LEN;

  if (params[4] <= REQUEST_SENSE_DATA_LEN)
  {
    hmsc->bot_data_length = params[4];
  }
  return 0;
}