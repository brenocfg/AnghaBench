#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t scsi_sense_tail; TYPE_2__* scsi_sense; } ;
struct TYPE_9__ {TYPE_4__ MSC_BOT_ClassData; } ;
typedef  TYPE_3__ usbd_cdc_msc_hid_state_t ;
typedef  int uint8_t ;
typedef  TYPE_4__ USBD_MSC_BOT_HandleTypeDef ;
struct TYPE_11__ {scalar_t__ pClassData; } ;
typedef  TYPE_5__ USBD_HandleTypeDef ;
struct TYPE_7__ {int ASC; } ;
struct TYPE_8__ {int Skey; TYPE_1__ w; } ;

/* Variables and functions */
 size_t SENSE_LIST_DEEPTH ; 

void SCSI_SenseCode(USBD_HandleTypeDef  *pdev, uint8_t lun, uint8_t sKey, uint8_t ASC)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = &((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->MSC_BOT_ClassData;

  hmsc->scsi_sense[hmsc->scsi_sense_tail].Skey  = sKey;
  hmsc->scsi_sense[hmsc->scsi_sense_tail].w.ASC = ASC << 8;
  hmsc->scsi_sense_tail++;
  if (hmsc->scsi_sense_tail == SENSE_LIST_DEEPTH)
  {
    hmsc->scsi_sense_tail = 0;
  }
}