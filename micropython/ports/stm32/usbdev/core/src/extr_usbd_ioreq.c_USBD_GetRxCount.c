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
typedef  int /*<<< orphan*/  USBD_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_LL_GetRxDataSize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

uint16_t  USBD_GetRxCount (USBD_HandleTypeDef  *pdev , uint8_t ep_addr)
{
  return USBD_LL_GetRxDataSize(pdev, ep_addr);
}