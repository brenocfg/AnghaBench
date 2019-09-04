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
typedef  int /*<<< orphan*/  mp_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_OBJ_NEW_QSTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_OBJ_SMALL_INT_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_builtin___import__ (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_const_none ; 
 int /*<<< orphan*/  qstr_str (int /*<<< orphan*/ ) ; 

mp_obj_t mp_import_name(qstr name, mp_obj_t fromlist, mp_obj_t level) {
    DEBUG_printf("import name '%s' level=%d\n", qstr_str(name), MP_OBJ_SMALL_INT_VALUE(level));

    // build args array
    mp_obj_t args[5];
    args[0] = MP_OBJ_NEW_QSTR(name);
    args[1] = mp_const_none; // TODO should be globals
    args[2] = mp_const_none; // TODO should be locals
    args[3] = fromlist;
    args[4] = level;

    // TODO lookup __import__ and call that instead of going straight to builtin implementation
    return mp_builtin___import__(5, args);
}