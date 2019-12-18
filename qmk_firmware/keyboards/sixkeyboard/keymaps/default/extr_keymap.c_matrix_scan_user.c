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
 int /*<<< orphan*/  bootloader_jump () ; 
 int /*<<< orphan*/  clear_keyboard () ; 
 int matrix_get_row (int) ; 

void matrix_scan_user(void) {
  // jump to bootloaer when all keys are pressed
  if (matrix_get_row(0) == 0b111 && matrix_get_row(1) == 0b111) {
    clear_keyboard();
    bootloader_jump();
  }
}