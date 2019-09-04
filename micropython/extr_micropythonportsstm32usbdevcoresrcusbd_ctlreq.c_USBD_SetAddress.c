#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_9__ {scalar_t__ wIndex; scalar_t__ wLength; scalar_t__ wValue; } ;
typedef  TYPE_1__ USBD_SetupReqTypedef ;
struct TYPE_10__ {scalar_t__ dev_state; int dev_address; } ;
typedef  TYPE_2__ USBD_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_CtlError (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  USBD_CtlSendStatus (TYPE_2__*) ; 
 int /*<<< orphan*/  USBD_LL_SetUSBAddress (TYPE_2__*,int) ; 
 scalar_t__ USBD_STATE_ADDRESSED ; 
 scalar_t__ USBD_STATE_CONFIGURED ; 
 scalar_t__ USBD_STATE_DEFAULT ; 

__attribute__((used)) static void USBD_SetAddress(USBD_HandleTypeDef *pdev ,
                            USBD_SetupReqTypedef *req)
{
  uint8_t  dev_addr;

  if ((req->wIndex == 0) && (req->wLength == 0))
  {
    dev_addr = (uint8_t)(req->wValue) & 0x7F;

    if (pdev->dev_state == USBD_STATE_CONFIGURED)
    {
      USBD_CtlError(pdev , req);
    }
    else
    {
      pdev->dev_address = dev_addr;
      USBD_LL_SetUSBAddress(pdev, dev_addr);
      USBD_CtlSendStatus(pdev);

      if (dev_addr != 0)
      {
        pdev->dev_state  = USBD_STATE_ADDRESSED;
      }
      else
      {
        pdev->dev_state  = USBD_STATE_DEFAULT;
      }
    }
  }
  else
  {
     USBD_CtlError(pdev , req);
  }
}