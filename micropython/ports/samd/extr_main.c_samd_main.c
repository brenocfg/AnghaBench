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

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_NEW_QSTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_OBJ_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_PYTHON_PRINTER ; 
 int /*<<< orphan*/  MP_QSTR_ ; 
 scalar_t__ PYEXEC_MODE_RAW_REPL ; 
 int /*<<< orphan*/  _eheap ; 
 int /*<<< orphan*/  _estack ; 
 int /*<<< orphan*/  _sheap ; 
 int /*<<< orphan*/  _sstack ; 
 int /*<<< orphan*/  gc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gc_sweep_all () ; 
 int /*<<< orphan*/  mp_deinit () ; 
 int /*<<< orphan*/  mp_init () ; 
 int /*<<< orphan*/  mp_obj_list_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_list_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mp_stack_set_limit (int) ; 
 int /*<<< orphan*/  mp_stack_set_top (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_sys_argv ; 
 int /*<<< orphan*/  mp_sys_path ; 
 scalar_t__ pyexec_friendly_repl () ; 
 scalar_t__ pyexec_mode_kind ; 
 scalar_t__ pyexec_raw_repl () ; 

void samd_main(void) {
    mp_stack_set_top(&_estack);
    mp_stack_set_limit(&_estack - &_sstack - 1024);

    for (;;) {
        gc_init(&_sheap, &_eheap);
        mp_init();
        mp_obj_list_init(MP_OBJ_TO_PTR(mp_sys_path), 0);
        mp_obj_list_append(mp_sys_path, MP_OBJ_NEW_QSTR(MP_QSTR_));
        mp_obj_list_init(MP_OBJ_TO_PTR(mp_sys_argv), 0);

        for (;;) {
            if (pyexec_mode_kind == PYEXEC_MODE_RAW_REPL) {
                if (pyexec_raw_repl() != 0) {
                    break;
                }
            } else {
                if (pyexec_friendly_repl() != 0) {
                    break;
                }
            }
        }

        mp_printf(MP_PYTHON_PRINTER, "MPY: soft reboot\n");
        gc_sweep_all();
        mp_deinit();
    }
}