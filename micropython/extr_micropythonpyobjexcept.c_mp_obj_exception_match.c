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
typedef  int /*<<< orphan*/  mp_obj_t ;
typedef  int /*<<< orphan*/  mp_const_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_get_type (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_is_exception_instance (int /*<<< orphan*/ ) ; 
 int mp_obj_is_subclass_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool mp_obj_exception_match(mp_obj_t exc, mp_const_obj_t exc_type) {
    // if exc is an instance of an exception, then extract and use its type
    if (mp_obj_is_exception_instance(exc)) {
        exc = MP_OBJ_FROM_PTR(mp_obj_get_type(exc));
    }
    return mp_obj_is_subclass_fast(exc, exc_type);
}