#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
struct TYPE_6__ {int servo_id; } ;
typedef  TYPE_1__ pyb_servo_obj_t ;
typedef  TYPE_1__* mp_obj_t ;

/* Variables and functions */
 TYPE_1__* MP_OBJ_NEW_SMALL_INT (int) ; 
 int servo_active_mask ; 

__attribute__((used)) static mp_obj_t servo_obj_attached(mp_obj_t self_in) {
    pyb_servo_obj_t *self = self_in;
    uint attached = (servo_active_mask & (1 << self->servo_id)) != 0;
    return MP_OBJ_NEW_SMALL_INT(attached);
}