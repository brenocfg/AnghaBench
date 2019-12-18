#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int started; int /*<<< orphan*/  hUSBDDevice; } ;
typedef  TYPE_1__ pyb_usbdd_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_Stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pyb_usbdd_stop(pyb_usbdd_obj_t *self) {
    if (self->started) {
        USBD_Stop(&self->hUSBDDevice);
        self->started = false;
    }
}