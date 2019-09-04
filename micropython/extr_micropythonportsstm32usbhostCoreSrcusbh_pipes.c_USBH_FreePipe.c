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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_3__ {int* Pipes; } ;
typedef  TYPE_1__ USBH_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBH_OK ; 

USBH_StatusTypeDef USBH_FreePipe  (USBH_HandleTypeDef *phost, uint8_t idx)
{
   if(idx < 11)
   {
	 phost->Pipes[idx] &= 0x7FFF;
   }
   return USBH_OK;
}