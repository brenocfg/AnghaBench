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
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_4__ {scalar_t__ len; scalar_t__ neg; } ;
struct TYPE_5__ {TYPE_1__ mpz; } ;
typedef  TYPE_2__ mp_obj_int_t ;
typedef  scalar_t__ mp_int_t ;

/* Variables and functions */
 scalar_t__ MP_OBJ_SMALL_INT_VALUE (int /*<<< orphan*/ ) ; 
 TYPE_2__* MP_OBJ_TO_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_is_small_int (int /*<<< orphan*/ ) ; 

int mp_obj_int_sign(mp_obj_t self_in) {
    if (mp_obj_is_small_int(self_in)) {
        mp_int_t val = MP_OBJ_SMALL_INT_VALUE(self_in);
        if (val < 0) {
            return -1;
        } else if (val > 0) {
            return 1;
        } else {
            return 0;
        }
    }
    mp_obj_int_t *self = MP_OBJ_TO_PTR(self_in);
    if (self->mpz.len == 0) {
        return 0;
    } else if (self->mpz.neg == 0) {
        return 1;
    } else {
        return -1;
    }
}