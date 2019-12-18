#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  USBD_SetupReqTypedef ;
struct TYPE_5__ {int dev_state; int /*<<< orphan*/  dev_config_status; int /*<<< orphan*/  dev_remote_wakeup; } ;
typedef  TYPE_1__ USBD_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_CtlError (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USBD_CtlSendData (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
#define  USBD_STATE_ADDRESSED 129 
#define  USBD_STATE_CONFIGURED 128 
 int /*<<< orphan*/  USB_CONFIG_REMOTE_WAKEUP ; 
 int /*<<< orphan*/  USB_CONFIG_SELF_POWERED ; 

__attribute__((used)) static void USBD_GetStatus(USBD_HandleTypeDef *pdev ,
                           USBD_SetupReqTypedef *req)
{


  switch (pdev->dev_state)
  {
  case USBD_STATE_ADDRESSED:
  case USBD_STATE_CONFIGURED:

#if ( USBD_SELF_POWERED == 1)
    pdev->dev_config_status = USB_CONFIG_SELF_POWERED;
#else
    pdev->dev_config_status = 0;
#endif

    if (pdev->dev_remote_wakeup)
    {
       pdev->dev_config_status |= USB_CONFIG_REMOTE_WAKEUP;
    }

    USBD_CtlSendData (pdev,
                      (uint8_t *)& pdev->dev_config_status,
                      2);
    break;

  default :
    USBD_CtlError(pdev , req);
    break;
  }
}