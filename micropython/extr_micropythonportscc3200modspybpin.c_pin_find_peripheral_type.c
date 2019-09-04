#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_5__ {int num_afs; TYPE_1__* af_list; } ;
typedef  TYPE_2__ pin_obj_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_4__ {scalar_t__ fn; scalar_t__ unit; scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_raise_ValueError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpexception_value_invalid_arguments ; 
 TYPE_2__* pin_find (int /*<<< orphan*/  const) ; 

uint8_t pin_find_peripheral_type (const mp_obj_t pin, uint8_t fn, uint8_t unit) {
    pin_obj_t *pin_o = pin_find(pin);
    for (int i = 0; i < pin_o->num_afs; i++) {
        if (pin_o->af_list[i].fn == fn && pin_o->af_list[i].unit == unit) {
            return pin_o->af_list[i].type;
        }
    }
    mp_raise_ValueError(mpexception_value_invalid_arguments);
}