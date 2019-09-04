#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t servo_id; int /*<<< orphan*/  max_usecs; int /*<<< orphan*/  min_usecs; } ;
typedef  TYPE_1__ pyb_servo_obj_t ;
typedef  TYPE_1__* mp_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  map_float_to_uint (float,float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float map_uint_to_float (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double) ; 
 TYPE_1__* mp_const_none ; 
 float mp_obj_get_float (TYPE_1__* const) ; 
 TYPE_1__* mp_obj_new_float (float) ; 
 int /*<<< orphan*/ * servo_ticks ; 
 int /*<<< orphan*/  usToTicks (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mp_obj_t servo_obj_angle(int n_args, const mp_obj_t *args) {
    pyb_servo_obj_t *self = args[0];
    if (n_args == 1) {
        // get
        float angle = map_uint_to_float(servo_ticks[self->servo_id],
                                        usToTicks(self->min_usecs),
                                        usToTicks(self->max_usecs),
                                        0.0, 180.0);
        return mp_obj_new_float(angle);
    }
    // Set
    float angle = mp_obj_get_float(args[1]);
    if (angle < 0.0F) {
        angle = 0.0F;
    }
    if (angle > 180.0F) {
        angle = 180.0F;
    }
    servo_ticks[self->servo_id] = map_float_to_uint(angle,
                                                    0.0F, 180.0F,
                                                    usToTicks(self->min_usecs),
                                                    usToTicks(self->max_usecs));
    return mp_const_none;
}