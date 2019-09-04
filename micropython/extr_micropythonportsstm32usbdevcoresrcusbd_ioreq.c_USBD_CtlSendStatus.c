#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USBD_StatusTypeDef ;
struct TYPE_4__ {int /*<<< orphan*/  ep0_state; } ;
typedef  TYPE_1__ USBD_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_EP0_STATUS_IN ; 
 int /*<<< orphan*/  USBD_LL_Transmit (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_OK ; 

USBD_StatusTypeDef  USBD_CtlSendStatus (USBD_HandleTypeDef  *pdev)
{

  /* Set EP0 State */
  pdev->ep0_state = USBD_EP0_STATUS_IN;

 /* Start the transfer */
  USBD_LL_Transmit (pdev, 0x00, NULL, 0);

  return USBD_OK;
}