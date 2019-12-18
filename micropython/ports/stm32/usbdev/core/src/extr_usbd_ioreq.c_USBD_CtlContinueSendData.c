#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  USBD_StatusTypeDef ;
typedef  int /*<<< orphan*/  USBD_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_LL_Transmit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_OK ; 

USBD_StatusTypeDef  USBD_CtlContinueSendData (USBD_HandleTypeDef  *pdev,
                                       uint8_t *pbuf,
                                       uint16_t len)
{
 /* Start the next transfer */
  USBD_LL_Transmit (pdev, 0x00, pbuf, len);

  return USBD_OK;
}