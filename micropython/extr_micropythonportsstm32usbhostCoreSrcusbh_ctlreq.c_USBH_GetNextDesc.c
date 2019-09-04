#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int bLength; } ;
typedef  TYPE_1__ USBH_DescHeader_t ;

/* Variables and functions */

USBH_DescHeader_t  *USBH_GetNextDesc (uint8_t   *pbuf, uint16_t  *ptr)
{
  USBH_DescHeader_t  *pnext;
 
  *ptr += ((USBH_DescHeader_t *)pbuf)->bLength;  
  pnext = (USBH_DescHeader_t *)((uint8_t *)pbuf + \
         ((USBH_DescHeader_t *)pbuf)->bLength);
 
  return(pnext);
}