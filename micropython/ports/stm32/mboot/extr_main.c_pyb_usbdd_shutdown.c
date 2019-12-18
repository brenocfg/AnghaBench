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
 int /*<<< orphan*/  pyb_usbdd ; 
 int /*<<< orphan*/  pyb_usbdd_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pyb_usbdd_shutdown(void) {
    pyb_usbdd_stop(&pyb_usbdd);
    return 0;
}