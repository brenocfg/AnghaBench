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
typedef  int /*<<< orphan*/  stlink_t ;

/* Variables and functions */
 scalar_t__ is_flash_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void wait_flash_busy_progress(stlink_t *sl) {
  while (is_flash_busy(sl)) {
    usleep(10000);
  }
}