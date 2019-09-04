#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ dSignature; int bLUN; int bCBLength; int /*<<< orphan*/ * CB; int /*<<< orphan*/  dDataLength; int /*<<< orphan*/  dTag; } ;
struct TYPE_13__ {int /*<<< orphan*/  dDataResidue; int /*<<< orphan*/  dTag; } ;
struct TYPE_16__ {scalar_t__ bot_state; scalar_t__ bot_data_length; int /*<<< orphan*/  bot_data; TYPE_2__ cbw; int /*<<< orphan*/  bot_status; TYPE_1__ csw; } ;
struct TYPE_15__ {TYPE_4__ MSC_BOT_ClassData; } ;
typedef  TYPE_3__ usbd_cdc_msc_hid_state_t ;
typedef  TYPE_4__ USBD_MSC_BOT_HandleTypeDef ;
struct TYPE_17__ {scalar_t__ pClassData; } ;
typedef  TYPE_5__ USBD_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  INVALID_CDB ; 
 int /*<<< orphan*/  MSC_BOT_Abort (TYPE_5__*) ; 
 int /*<<< orphan*/  MSC_BOT_SendCSW (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSC_BOT_SendData (TYPE_5__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MSC_OUT_EP ; 
 scalar_t__ SCSI_ProcessCmd (TYPE_5__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCSI_SenseCode (TYPE_5__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ USBD_BOT_CBW_LENGTH ; 
 scalar_t__ USBD_BOT_CBW_SIGNATURE ; 
 scalar_t__ USBD_BOT_DATA_IN ; 
 scalar_t__ USBD_BOT_DATA_OUT ; 
 scalar_t__ USBD_BOT_LAST_DATA_IN ; 
 scalar_t__ USBD_BOT_NO_DATA ; 
 int /*<<< orphan*/  USBD_BOT_STATUS_ERROR ; 
 int /*<<< orphan*/  USBD_CSW_CMD_FAILED ; 
 int /*<<< orphan*/  USBD_CSW_CMD_PASSED ; 
 scalar_t__ USBD_LL_GetRxDataSize (TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void  MSC_BOT_CBW_Decode (USBD_HandleTypeDef  *pdev)
{
  USBD_MSC_BOT_HandleTypeDef *hmsc = &((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->MSC_BOT_ClassData;

  hmsc->csw.dTag = hmsc->cbw.dTag;
  hmsc->csw.dDataResidue = hmsc->cbw.dDataLength;

  if ((USBD_LL_GetRxDataSize (pdev ,MSC_OUT_EP) != USBD_BOT_CBW_LENGTH) ||
      (hmsc->cbw.dSignature != USBD_BOT_CBW_SIGNATURE)||
        (hmsc->cbw.bLUN > 1) ||
          (hmsc->cbw.bCBLength < 1) ||
            (hmsc->cbw.bCBLength > 16))
  {

    SCSI_SenseCode(pdev,
                   hmsc->cbw.bLUN,
                   ILLEGAL_REQUEST,
                   INVALID_CDB);

    hmsc->bot_status = USBD_BOT_STATUS_ERROR;
    MSC_BOT_Abort(pdev);

  }
  else
  {
    if(SCSI_ProcessCmd(pdev,
                       hmsc->cbw.bLUN,
                       &hmsc->cbw.CB[0]) < 0)
    {
      if(hmsc->bot_state == USBD_BOT_NO_DATA)
      {
       MSC_BOT_SendCSW (pdev,
                         USBD_CSW_CMD_FAILED);
      }
      else
      {
        MSC_BOT_Abort(pdev);
      }
    }
    /*Burst xfer handled internally*/
    else if ((hmsc->bot_state != USBD_BOT_DATA_IN) &&
             (hmsc->bot_state != USBD_BOT_DATA_OUT) &&
             (hmsc->bot_state != USBD_BOT_LAST_DATA_IN))
    {
      if (hmsc->bot_data_length > 0)
      {
        MSC_BOT_SendData(pdev,
                         hmsc->bot_data,
                         hmsc->bot_data_length);
      }
      else if (hmsc->bot_data_length == 0)
      {
        MSC_BOT_SendCSW (pdev,
                         USBD_CSW_CMD_PASSED);
      }
    }
  }
}