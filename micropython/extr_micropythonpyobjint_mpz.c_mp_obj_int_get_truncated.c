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
struct TYPE_3__ {int /*<<< orphan*/  mpz; } ;
typedef  TYPE_1__ mp_obj_int_t ;
typedef  int /*<<< orphan*/  mp_int_t ;
typedef  int /*<<< orphan*/  mp_const_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_SMALL_INT_VALUE (int /*<<< orphan*/ ) ; 
 TYPE_1__* MP_OBJ_TO_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_is_small_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_hash (int /*<<< orphan*/ *) ; 

mp_int_t mp_obj_int_get_truncated(mp_const_obj_t self_in) {
    if (mp_obj_is_small_int(self_in)) {
        return MP_OBJ_SMALL_INT_VALUE(self_in);
    } else {
        const mp_obj_int_t *self = MP_OBJ_TO_PTR(self_in);
        // hash returns actual int value if it fits in mp_int_t
        return mpz_hash(&self->mpz);
    }
}