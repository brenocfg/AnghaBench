#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  MAPR; } ;
struct TYPE_3__ {int /*<<< orphan*/  DR10; } ;

/* Variables and functions */
 TYPE_2__* AFIO ; 
 int /*<<< orphan*/  AFIO_MAPR_SWJ_CFG_JTAGDISABLE ; 
 TYPE_1__* BKP ; 
 int /*<<< orphan*/  RTC_BOOTLOADER_FLAG ; 

void boardInit(void) {
   //JTAG-DP Disabled and SW-DP Enabled
   AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
   //Set backup register DR10 to enter bootloader on reset
   BKP->DR10 = RTC_BOOTLOADER_FLAG;
}