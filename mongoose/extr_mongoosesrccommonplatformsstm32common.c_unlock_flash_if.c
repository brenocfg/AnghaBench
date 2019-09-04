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
 scalar_t__ is_flash_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  unlock_flash (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int unlock_flash_if(stlink_t *sl) {
  /* unlock flash if already locked */

  if (is_flash_locked(sl)) {
    unlock_flash(sl);
    if (is_flash_locked(sl)) {
      printf("Failed to unlock flash!\n");
      return -1;
    }
  }
  return 0;
}