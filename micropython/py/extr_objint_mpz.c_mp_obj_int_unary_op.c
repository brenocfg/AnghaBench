#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int mp_unary_op_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_14__ {int /*<<< orphan*/  neg; } ;
struct TYPE_13__ {TYPE_2__ mpz; } ;
typedef  TYPE_1__ mp_obj_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (TYPE_1__*) ; 
 int /*<<< orphan*/  MP_OBJ_NEW_SMALL_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_OBJ_NULL ; 
 TYPE_1__* MP_OBJ_TO_PTR (int /*<<< orphan*/ ) ; 
#define  MP_UNARY_OP_ABS 133 
#define  MP_UNARY_OP_BOOL 132 
#define  MP_UNARY_OP_HASH 131 
#define  MP_UNARY_OP_INVERT 130 
#define  MP_UNARY_OP_NEGATIVE 129 
#define  MP_UNARY_OP_POSITIVE 128 
 TYPE_1__* mp_obj_int_new_mpz () ; 
 int /*<<< orphan*/  mp_obj_new_bool (int) ; 
 int /*<<< orphan*/  mpz_abs_inpl (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  mpz_hash (TYPE_2__*) ; 
 int /*<<< orphan*/  mpz_is_zero (TYPE_2__*) ; 
 int /*<<< orphan*/  mpz_neg_inpl (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  mpz_not_inpl (TYPE_2__*,TYPE_2__*) ; 

mp_obj_t mp_obj_int_unary_op(mp_unary_op_t op, mp_obj_t o_in) {
    mp_obj_int_t *o = MP_OBJ_TO_PTR(o_in);
    switch (op) {
        case MP_UNARY_OP_BOOL: return mp_obj_new_bool(!mpz_is_zero(&o->mpz));
        case MP_UNARY_OP_HASH: return MP_OBJ_NEW_SMALL_INT(mpz_hash(&o->mpz));
        case MP_UNARY_OP_POSITIVE: return o_in;
        case MP_UNARY_OP_NEGATIVE: { mp_obj_int_t *o2 = mp_obj_int_new_mpz(); mpz_neg_inpl(&o2->mpz, &o->mpz); return MP_OBJ_FROM_PTR(o2); }
        case MP_UNARY_OP_INVERT: { mp_obj_int_t *o2 = mp_obj_int_new_mpz(); mpz_not_inpl(&o2->mpz, &o->mpz); return MP_OBJ_FROM_PTR(o2); }
        case MP_UNARY_OP_ABS: {
            mp_obj_int_t *self = MP_OBJ_TO_PTR(o_in);
            if (self->mpz.neg == 0) {
                return o_in;
            }
            mp_obj_int_t *self2 = mp_obj_int_new_mpz();
            mpz_abs_inpl(&self2->mpz, &self->mpz);
            return MP_OBJ_FROM_PTR(self2);
        }
        default: return MP_OBJ_NULL; // op not supported
    }
}