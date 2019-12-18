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
 int /*<<< orphan*/  enter_bootloader_mode_if_requested () ; 
 int /*<<< orphan*/  stm32_clock_init () ; 

void __early_init(void) {
  enter_bootloader_mode_if_requested();
  stm32_clock_init();
}