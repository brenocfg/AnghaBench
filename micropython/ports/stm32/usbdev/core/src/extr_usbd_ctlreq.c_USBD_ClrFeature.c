#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  wValue; } ;
typedef  TYPE_2__ USBD_SetupReqTypedef ;
struct TYPE_13__ {int dev_state; TYPE_1__* pClass; int /*<<< orphan*/  dev_remote_wakeup; } ;
typedef  TYPE_3__ USBD_HandleTypeDef ;
struct TYPE_11__ {int /*<<< orphan*/  (* Setup ) (TYPE_3__*,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_CtlError (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  USBD_CtlSendStatus (TYPE_3__*) ; 
#define  USBD_STATE_ADDRESSED 129 
#define  USBD_STATE_CONFIGURED 128 
 int /*<<< orphan*/  USB_FEATURE_REMOTE_WAKEUP ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static void USBD_ClrFeature(USBD_HandleTypeDef *pdev ,
                            USBD_SetupReqTypedef *req)
{
  switch (pdev->dev_state)
  {
  case USBD_STATE_ADDRESSED:
  case USBD_STATE_CONFIGURED:
    if (req->wValue == USB_FEATURE_REMOTE_WAKEUP)
    {
      pdev->dev_remote_wakeup = 0;
      pdev->pClass->Setup (pdev, req);
      USBD_CtlSendStatus(pdev);
    }
    break;

  default :
     USBD_CtlError(pdev , req);
    break;
  }
}