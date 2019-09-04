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
 int /*<<< orphan*/  USBD_LL_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_LL_Start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pyb_usbdd_start(pyb_usbdd_obj_t *self) {
    if (!self->started) {
        #if defined(STM32H7)
        PWR->CR3 |= PWR_CR3_USB33DEN;
        while (!(PWR->CR3 & PWR_CR3_USB33RDY)) {
        }
        #endif
        USBD_LL_Init(&self->hUSBDDevice, 0);
        USBD_LL_Start(&self->hUSBDDevice);
        self->started = true;
    }
}