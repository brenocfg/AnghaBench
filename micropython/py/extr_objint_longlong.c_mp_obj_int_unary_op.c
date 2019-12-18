#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int mp_unary_op_t ;
typedef  TYPE_1__* mp_obj_t ;
struct TYPE_13__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ mp_obj_int_t ;
typedef  int /*<<< orphan*/  mp_int_t ;

/* Variables and functions */
 TYPE_1__* MP_OBJ_FROM_PTR (TYPE_1__*) ; 
 TYPE_1__* MP_OBJ_NEW_SMALL_INT (int /*<<< orphan*/ ) ; 
 TYPE_1__* MP_OBJ_NULL ; 
 TYPE_1__* MP_OBJ_TO_PTR (TYPE_1__*) ; 
#define  MP_UNARY_OP_ABS 133 
#define  MP_UNARY_OP_BOOL 132 
#define  MP_UNARY_OP_HASH 131 
#define  MP_UNARY_OP_INVERT 130 
#define  MP_UNARY_OP_NEGATIVE 129 
#define  MP_UNARY_OP_POSITIVE 128 
 TYPE_1__* mp_obj_new_bool (int) ; 
 TYPE_1__* mp_obj_new_int_from_ll (int /*<<< orphan*/ ) ; 

mp_obj_t mp_obj_int_unary_op(mp_unary_op_t op, mp_obj_t o_in) {
    mp_obj_int_t *o = o_in;
    switch (op) {
        case MP_UNARY_OP_BOOL: return mp_obj_new_bool(o->val != 0);

        // truncate value to fit in mp_int_t, which gives the same hash as
        // small int if the value fits without truncation
        case MP_UNARY_OP_HASH: return MP_OBJ_NEW_SMALL_INT((mp_int_t)o->val);

        case MP_UNARY_OP_POSITIVE: return o_in;
        case MP_UNARY_OP_NEGATIVE: return mp_obj_new_int_from_ll(-o->val);
        case MP_UNARY_OP_INVERT: return mp_obj_new_int_from_ll(~o->val);
        case MP_UNARY_OP_ABS: {
            mp_obj_int_t *self = MP_OBJ_TO_PTR(o_in);
            if (self->val >= 0) {
                return o_in;
            }
            self = mp_obj_new_int_from_ll(self->val);
            // TODO could overflow long long
            self->val = -self->val;
            return MP_OBJ_FROM_PTR(self);
        }
        default: return MP_OBJ_NULL; // op not supported
    }
}