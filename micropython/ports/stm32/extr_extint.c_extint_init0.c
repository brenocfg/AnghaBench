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
 int /*<<< orphan*/  EXTI_Mode_Interrupt ; 
 scalar_t__ MP_OBJ_SENTINEL ; 
 scalar_t__* MP_STATE_PORT (int /*<<< orphan*/ ) ; 
 int PYB_EXTI_NUM_VECTORS ; 
 scalar_t__ mp_const_none ; 
 int /*<<< orphan*/  pyb_extint_callback ; 
 int /*<<< orphan*/ * pyb_extint_mode ; 

void extint_init0(void) {
    for (int i = 0; i < PYB_EXTI_NUM_VECTORS; i++) {
        if (MP_STATE_PORT(pyb_extint_callback)[i] == MP_OBJ_SENTINEL) {
            continue;
        }
        MP_STATE_PORT(pyb_extint_callback)[i] = mp_const_none;
        pyb_extint_mode[i] = EXTI_Mode_Interrupt;
   }
}