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
typedef  int /*<<< orphan*/  MP_STATE_PORT ;

/* Variables and functions */
 int /*<<< orphan*/  mp_obj_new_exception (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_type_KeyboardInterrupt ; 

void mp_hal_init(void) {
    MP_STATE_PORT(keyboard_interrupt_obj) = mp_obj_new_exception(&mp_type_KeyboardInterrupt);
}