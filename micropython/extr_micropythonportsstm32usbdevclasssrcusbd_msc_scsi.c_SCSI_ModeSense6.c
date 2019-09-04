#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int bot_data_length; int /*<<< orphan*/ * bot_data; } ;
struct TYPE_5__ {TYPE_2__ MSC_BOT_ClassData; } ;
typedef  TYPE_1__ usbd_cdc_msc_hid_state_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  TYPE_2__ USBD_MSC_BOT_HandleTypeDef ;
struct TYPE_7__ {scalar_t__ pClassData; } ;
typedef  TYPE_3__ USBD_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/ * MSC_Mode_Sense6_data ; 

__attribute__((used)) static int8_t SCSI_ModeSense6 (USBD_HandleTypeDef  *pdev, uint8_t lun, uint8_t *params)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = &((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->MSC_BOT_ClassData;
  uint16_t len = 8 ;
  hmsc->bot_data_length = len;

  while (len)
  {
    len--;
    hmsc->bot_data[len] = MSC_Mode_Sense6_data[len];
  }
  return 0;
}