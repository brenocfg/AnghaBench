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
 scalar_t__ MICROPY_ERROR_REPORTING ; 
 scalar_t__ MICROPY_ERROR_REPORTING_TERSE ; 
 scalar_t__ MP_OBJ_NULL ; 
 scalar_t__ MP_OBJ_SMALL_INT_VALUE (scalar_t__ const) ; 
 int /*<<< orphan*/  mp_module_call_init (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mp_module_get (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_module_search_umodule (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_new_exception_msg_varg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_str_get_qstr (scalar_t__ const) ; 
 int /*<<< orphan*/  mp_raise_NotImplementedError (char*) ; 
 int /*<<< orphan*/  mp_raise_msg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mp_type_ImportError ; 
 int /*<<< orphan*/  nlr_raise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qstr_str (int /*<<< orphan*/ ) ; 

mp_obj_t mp_builtin___import__(size_t n_args, const mp_obj_t *args) {
    // Check that it's not a relative import
    if (n_args >= 5 && MP_OBJ_SMALL_INT_VALUE(args[4]) != 0) {
        mp_raise_NotImplementedError("relative import");
    }

    // Check if module already exists, and return it if it does
    qstr module_name_qstr = mp_obj_str_get_qstr(args[0]);
    mp_obj_t module_obj = mp_module_get(module_name_qstr);
    if (module_obj != MP_OBJ_NULL) {
        return module_obj;
    }

    #if MICROPY_MODULE_WEAK_LINKS
    // Check if there is a weak link to this module
    module_obj = mp_module_search_umodule(qstr_str(module_name_qstr));
    if (module_obj != MP_OBJ_NULL) {
        // Found weak-linked module
        mp_module_call_init(module_name_qstr, module_obj);
        return module_obj;
    }
    #endif

    // Couldn't find the module, so fail
    if (MICROPY_ERROR_REPORTING == MICROPY_ERROR_REPORTING_TERSE) {
        mp_raise_msg(&mp_type_ImportError, "module not found");
    } else {
        nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_ImportError,
            "no module named '%q'", module_name_qstr));
    }
}