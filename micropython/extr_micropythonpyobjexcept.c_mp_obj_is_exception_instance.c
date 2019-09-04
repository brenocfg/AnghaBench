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

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_get_type (int /*<<< orphan*/ ) ; 
 int mp_obj_is_exception_type (int /*<<< orphan*/ ) ; 

bool mp_obj_is_exception_instance(mp_obj_t self_in) {
    return mp_obj_is_exception_type(MP_OBJ_FROM_PTR(mp_obj_get_type(self_in)));
}