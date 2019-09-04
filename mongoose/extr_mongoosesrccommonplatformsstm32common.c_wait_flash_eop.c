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
 scalar_t__ is_flash_eop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __attribute__((unused)) wait_flash_eop(stlink_t *sl) {
  /* todo: add some delays here */
  while (is_flash_eop(sl) == 0)
    ;
}