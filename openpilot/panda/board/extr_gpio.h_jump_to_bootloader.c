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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ BOOT_NORMAL ; 
 int /*<<< orphan*/  NVIC_SystemReset () ; 
 scalar_t__ enter_bootloader_mode ; 

void jump_to_bootloader(void) {
  // do enter bootloader
  enter_bootloader_mode = 0;
  void (*bootloader)(void) = (void (*)(void)) (*((uint32_t *)0x1fff0004));

  // jump to bootloader
  bootloader();

  // reset on exit
  enter_bootloader_mode = BOOT_NORMAL;
  NVIC_SystemReset();
}