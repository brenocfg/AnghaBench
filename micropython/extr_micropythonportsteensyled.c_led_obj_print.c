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
struct TYPE_4__ {int /*<<< orphan*/  led_id; } ;
typedef  TYPE_1__ pyb_led_obj_t ;
typedef  int /*<<< orphan*/  mp_print_t ;
typedef  int /*<<< orphan*/  mp_print_kind_t ;
typedef  TYPE_1__* mp_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  mp_printf (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ ) ; 

void led_obj_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    pyb_led_obj_t *self = self_in;
    (void)kind;
    mp_printf(print, "<LED %lu>", self->led_id);
}