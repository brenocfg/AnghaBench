#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int bot_data_length; int* bot_data; TYPE_1__* bdev_ops; } ;
struct TYPE_7__ {TYPE_3__ MSC_BOT_ClassData; } ;
typedef  TYPE_2__ usbd_cdc_msc_hid_state_t ;
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  TYPE_3__ USBD_MSC_BOT_HandleTypeDef ;
struct TYPE_9__ {scalar_t__ pClassData; } ;
typedef  TYPE_4__ USBD_HandleTypeDef ;
struct TYPE_6__ {int /*<<< orphan*/ * pInquiry; } ;

/* Variables and functions */
 int LENGTH_INQUIRY_PAGE00 ; 
 scalar_t__ MSC_Page00_Inquiry_Data ; 
 int STANDARD_INQUIRY_DATA_LEN ; 

__attribute__((used)) static int8_t  SCSI_Inquiry(USBD_HandleTypeDef  *pdev, uint8_t lun, uint8_t *params)
{
  uint8_t* pPage;
  uint16_t len;
  USBD_MSC_BOT_HandleTypeDef *hmsc = &((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->MSC_BOT_ClassData;

  if (params[1] & 0x01)/*Evpd is set*/
  {
    pPage = (uint8_t *)MSC_Page00_Inquiry_Data;
    len = LENGTH_INQUIRY_PAGE00;
  }
  else
  {

    pPage = (uint8_t *)&hmsc->bdev_ops->pInquiry[lun * STANDARD_INQUIRY_DATA_LEN];
    len = pPage[4] + 5;

    if (params[4] <= len)
    {
      len = params[4];
    }
  }
  hmsc->bot_data_length = len;

  while (len)
  {
    len--;
    hmsc->bot_data[len] = pPage[len];
  }
  return 0;
}