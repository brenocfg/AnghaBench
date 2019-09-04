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
typedef  int mp_unary_op_t ;
typedef  int /*<<< orphan*/  mp_uint_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_NEW_SMALL_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_OBJ_NULL ; 
#define  MP_UNARY_OP_HASH 128 

mp_obj_t mp_generic_unary_op(mp_unary_op_t op, mp_obj_t o_in) {
    switch (op) {
        case MP_UNARY_OP_HASH: return MP_OBJ_NEW_SMALL_INT((mp_uint_t)o_in);
        default: return MP_OBJ_NULL; // op not supported
    }
}