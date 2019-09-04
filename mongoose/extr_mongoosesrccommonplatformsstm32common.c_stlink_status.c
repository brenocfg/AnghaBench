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
 int _stlink_usb_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stlink_core_stat (int /*<<< orphan*/ *) ; 

int stlink_status(stlink_t *sl) {
  int ret;

  ret = _stlink_usb_status(sl);
  stlink_core_stat(sl);

  return ret;
}