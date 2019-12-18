#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ string_image_facade_t ;
typedef  int mp_unary_op_t ;
typedef  scalar_t__ mp_obj_t ;

/* Variables and functions */
 scalar_t__ MP_OBJ_NULL ; 
#define  MP_UNARY_OP_LEN 128 
 scalar_t__ mp_obj_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mp_obj_t facade_unary_op(mp_unary_op_t op, mp_obj_t self_in) {
    string_image_facade_t *self = (string_image_facade_t *)self_in;
    switch (op) {
        case MP_UNARY_OP_LEN:
            return mp_obj_len(self->string);
        default: return MP_OBJ_NULL; // op not supported
    }
}