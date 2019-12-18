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
typedef  int /*<<< orphan*/  qstr ;
typedef  scalar_t__ mp_obj_t ;

/* Variables and functions */
 scalar_t__ MP_OBJ_NULL ; 
 int /*<<< orphan*/  mp_load_method (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mp_load_method_maybe (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ mp_obj_new_bound_meth (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static inline mp_obj_t mp_load_attr_default(mp_obj_t base, qstr attr, mp_obj_t defval) {
    mp_obj_t dest[2];
    // use load_method, raising or not raising exception
    ((defval == MP_OBJ_NULL) ? mp_load_method : mp_load_method_maybe)(base, attr, dest);
    if (dest[0] == MP_OBJ_NULL) {
        return defval;
    } else if (dest[1] == MP_OBJ_NULL) {
        // load_method returned just a normal attribute
        return dest[0];
    } else {
        // load_method returned a method, so build a bound method object
        return mp_obj_new_bound_meth(dest[0], dest[1]);
    }
}