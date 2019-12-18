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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_KEYB ; 
 int /*<<< orphan*/  adb_host_dev_recv (int /*<<< orphan*/ ) ; 

uint16_t adb_host_kbd_recv(void) { return adb_host_dev_recv(ADDR_KEYB); }