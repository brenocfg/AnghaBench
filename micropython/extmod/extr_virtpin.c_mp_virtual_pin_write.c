#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* ioctl ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ mp_pin_p_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_6__ {TYPE_1__* type; } ;
typedef  TYPE_3__ mp_obj_base_t ;
struct TYPE_4__ {scalar_t__ protocol; } ;

/* Variables and functions */
 scalar_t__ MP_OBJ_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_PIN_WRITE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void mp_virtual_pin_write(mp_obj_t pin, int value) {
    mp_obj_base_t* s = (mp_obj_base_t*)MP_OBJ_TO_PTR(pin);
    mp_pin_p_t *pin_p = (mp_pin_p_t*)s->type->protocol;
    pin_p->ioctl(pin, MP_PIN_WRITE, value, NULL);
}