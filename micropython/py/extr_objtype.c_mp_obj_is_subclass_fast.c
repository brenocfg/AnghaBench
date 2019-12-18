#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* parent; } ;
typedef  TYPE_1__ mp_obj_type_t ;
struct TYPE_7__ {int len; int /*<<< orphan*/ * items; } ;
typedef  TYPE_2__ mp_obj_tuple_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_8__ {int /*<<< orphan*/ * type; } ;
typedef  TYPE_3__ mp_obj_base_t ;
typedef  int /*<<< orphan*/  mp_const_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (TYPE_2__*) ; 
 TYPE_1__* MP_OBJ_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_is_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_type_tuple ; 
 int /*<<< orphan*/  mp_type_type ; 

bool mp_obj_is_subclass_fast(mp_const_obj_t object, mp_const_obj_t classinfo) {
    for (;;) {
        if (object == classinfo) {
            return true;
        }

        // not equivalent classes, keep searching base classes

        // object should always be a type object, but just return false if it's not
        if (!mp_obj_is_type(object, &mp_type_type)) {
            return false;
        }

        const mp_obj_type_t *self = MP_OBJ_TO_PTR(object);

        if (self->parent == NULL) {
            // type has no parents
            return false;
        #if MICROPY_MULTIPLE_INHERITANCE
        } else if (((mp_obj_base_t*)self->parent)->type == &mp_type_tuple) {
            // get the base objects (they should be type objects)
            const mp_obj_tuple_t *parent_tuple = self->parent;
            const mp_obj_t *item = parent_tuple->items;
            const mp_obj_t *top = item + parent_tuple->len - 1;

            // iterate through the base objects
            for (; item < top; ++item) {
                if (mp_obj_is_subclass_fast(*item, classinfo)) {
                    return true;
                }
            }

            // search last base (simple tail recursion elimination)
            object = *item;
        #endif
        } else {
            // type has 1 parent
            object = MP_OBJ_FROM_PTR(self->parent);
        }
    }
}