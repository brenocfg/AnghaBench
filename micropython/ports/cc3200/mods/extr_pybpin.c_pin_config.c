#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint ;
struct TYPE_4__ {int af; int value; int used; void* strength; void* pull; void* mode; } ;
typedef  TYPE_1__ pin_obj_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
typedef  int /*<<< orphan*/  WakeUpCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  pin_obj_configure (TYPE_1__ const*) ; 
 int /*<<< orphan*/  pyb_sleep_add (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

void pin_config (pin_obj_t *self, int af, uint mode, uint pull, int value, uint strength) {
    self->mode = mode, self->pull = pull, self->strength = strength;
    // if af is -1, then we want to keep it as it is
    if (af != -1) {
        self->af = af;
    }

    // if value is -1, then we want to keep it as it is
    if (value != -1) {
        self->value = value;
    }

    // mark the pin as used
    self->used = true;
    pin_obj_configure ((const pin_obj_t *)self);

    // register it with the sleep module
    pyb_sleep_add ((const mp_obj_t)self, (WakeUpCB_t)pin_obj_configure);
}