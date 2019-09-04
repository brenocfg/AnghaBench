#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int wLength; } ;
typedef  TYPE_1__ USBD_SetupReqTypedef ;
struct TYPE_9__ {int dev_state; int /*<<< orphan*/  dev_config; int /*<<< orphan*/  dev_default_config; } ;
typedef  TYPE_2__ USBD_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_CtlError (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  USBD_CtlSendData (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
#define  USBD_STATE_ADDRESSED 129 
#define  USBD_STATE_CONFIGURED 128 

__attribute__((used)) static void USBD_GetConfig(USBD_HandleTypeDef *pdev ,
                           USBD_SetupReqTypedef *req)
{

  if (req->wLength != 1)
  {
     USBD_CtlError(pdev , req);
  }
  else
  {
    switch (pdev->dev_state )
    {
    case USBD_STATE_ADDRESSED:
      pdev->dev_default_config = 0;
      USBD_CtlSendData (pdev,
                        (uint8_t *)&pdev->dev_default_config,
                        1);
      break;

    case USBD_STATE_CONFIGURED:

      USBD_CtlSendData (pdev,
                        (uint8_t *)&pdev->dev_config,
                        1);
      break;

    default:
       USBD_CtlError(pdev , req);
      break;
    }
  }
}