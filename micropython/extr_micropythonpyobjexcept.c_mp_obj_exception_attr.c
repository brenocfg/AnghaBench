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
typedef  scalar_t__ qstr ;
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_4__ {int /*<<< orphan*/ * type; } ;
struct TYPE_5__ {TYPE_1__ base; int /*<<< orphan*/  args; scalar_t__ traceback_len; } ;
typedef  TYPE_2__ mp_obj_exception_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_OBJ_NULL ; 
 TYPE_2__* MP_OBJ_TO_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ MP_QSTR___traceback__ ; 
 scalar_t__ MP_QSTR_args ; 
 scalar_t__ MP_QSTR_value ; 
 int /*<<< orphan*/  mp_const_none ; 
 int /*<<< orphan*/  mp_obj_exception_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_type_StopIteration ; 

void mp_obj_exception_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest) {
    mp_obj_exception_t *self = MP_OBJ_TO_PTR(self_in);
    if (dest[0] != MP_OBJ_NULL) {
        // store/delete attribute
        if (attr == MP_QSTR___traceback__ && dest[1] == mp_const_none) {
            // We allow 'exc.__traceback__ = None' assignment as low-level
            // optimization of pre-allocating exception instance and raising
            // it repeatedly - this avoids memory allocation during raise.
            // However, uPy will keep adding traceback entries to such
            // exception instance, so before throwing it, traceback should
            // be cleared like above.
            self->traceback_len = 0;
            dest[0] = MP_OBJ_NULL; // indicate success
        }
        return;
    }
    if (attr == MP_QSTR_args) {
        dest[0] = MP_OBJ_FROM_PTR(self->args);
    } else if (self->base.type == &mp_type_StopIteration && attr == MP_QSTR_value) {
        dest[0] = mp_obj_exception_get_value(self_in);
    }
}