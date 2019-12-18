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
typedef  int /*<<< orphan*/  qstr ;
struct TYPE_4__ {int /*<<< orphan*/ * ret_val; } ;
typedef  TYPE_1__ nlr_buf_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_5__ {int /*<<< orphan*/ * type; } ;
typedef  TYPE_2__ mp_obj_base_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_load_method_maybe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_obj_is_subclass_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_type_AttributeError ; 
 int /*<<< orphan*/  nlr_pop () ; 
 scalar_t__ nlr_push (TYPE_1__*) ; 
 int /*<<< orphan*/  nlr_raise (int /*<<< orphan*/ ) ; 

void mp_load_method_protected(mp_obj_t obj, qstr attr, mp_obj_t *dest, bool catch_all_exc) {
    nlr_buf_t nlr;
    if (nlr_push(&nlr) == 0) {
        mp_load_method_maybe(obj, attr, dest);
        nlr_pop();
    } else {
        if (!catch_all_exc
            && !mp_obj_is_subclass_fast(MP_OBJ_FROM_PTR(((mp_obj_base_t*)nlr.ret_val)->type),
                MP_OBJ_FROM_PTR(&mp_type_AttributeError))) {
            // Re-raise the exception
            nlr_raise(MP_OBJ_FROM_PTR(nlr.ret_val));
        }
    }
}