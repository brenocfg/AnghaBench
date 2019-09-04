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
 scalar_t__ RAW3270_FIRSTMINOR ; 
 int /*<<< orphan*/  tty3270_driver ; 
 int /*<<< orphan*/  tty_register_device (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tty3270_create_cb(int minor)
{
	tty_register_device(tty3270_driver, minor - RAW3270_FIRSTMINOR, NULL);
}