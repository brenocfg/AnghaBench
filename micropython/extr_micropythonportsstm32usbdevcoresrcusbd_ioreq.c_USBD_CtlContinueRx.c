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
 int /*<<< orphan*/  USBD_LL_PrepareReceive (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_OK ; 

USBD_StatusTypeDef  USBD_CtlContinueRx (USBD_HandleTypeDef  *pdev,
                                          uint8_t *pbuf,
                                          uint16_t len)
{

  USBD_LL_PrepareReceive (pdev,
                          0,
                          pbuf,
                          len);
  return USBD_OK;
}