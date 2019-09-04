#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint16_t ;
typedef  int /*<<< orphan*/  USBD_StatusTypeDef ;
struct TYPE_6__ {TYPE_1__* ep_in; int /*<<< orphan*/  ep0_state; } ;
typedef  TYPE_2__ USBD_HandleTypeDef ;
struct TYPE_5__ {void* rem_length; void* total_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_EP0_DATA_IN ; 
 int /*<<< orphan*/  USBD_LL_Transmit (TYPE_2__*,int,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  USBD_OK ; 

USBD_StatusTypeDef  USBD_CtlSendData (USBD_HandleTypeDef  *pdev,
                               uint8_t *pbuf,
                               uint16_t len)
{
  /* Set EP0 State */
  pdev->ep0_state          = USBD_EP0_DATA_IN;
  pdev->ep_in[0].total_length = len;
  pdev->ep_in[0].rem_length   = len;
 /* Start the transfer */
  USBD_LL_Transmit (pdev, 0x00, pbuf, len);

  return USBD_OK;
}