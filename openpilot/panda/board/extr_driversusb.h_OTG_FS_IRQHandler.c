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

/* Variables and functions */
 int /*<<< orphan*/  NVIC_DisableIRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVIC_EnableIRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OTG_FS_IRQn ; 
 int /*<<< orphan*/  usb_irqhandler () ; 

void OTG_FS_IRQHandler(void) {
  NVIC_DisableIRQ(OTG_FS_IRQn);
  //__disable_irq();
  usb_irqhandler();
  //__enable_irq();
  NVIC_EnableIRQ(OTG_FS_IRQn);
}