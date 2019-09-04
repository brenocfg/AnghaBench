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
 scalar_t__ CONFIG_MAIN_STACK_SIZE ; 
 int /*<<< orphan*/  MP_OBJ_NEW_QSTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_QSTR_ ; 
 scalar_t__ PYEXEC_MODE_RAW_REPL ; 
 int /*<<< orphan*/  init_zephyr () ; 
 int /*<<< orphan*/  mp_init () ; 
 int /*<<< orphan*/  mp_obj_list_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_list_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_stack_set_limit (scalar_t__) ; 
 int /*<<< orphan*/  mp_stack_set_top (char*) ; 
 int /*<<< orphan*/  mp_sys_argv ; 
 int /*<<< orphan*/  mp_sys_path ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ pyexec_friendly_repl () ; 
 scalar_t__ pyexec_mode_kind ; 
 scalar_t__ pyexec_raw_repl () ; 
 char* stack_top ; 

int real_main(void) {
    int stack_dummy;
    stack_top = (char*)&stack_dummy;
    mp_stack_set_top(stack_top);
    // Make MicroPython's stack limit somewhat smaller than full stack available
    mp_stack_set_limit(CONFIG_MAIN_STACK_SIZE - 512);

    init_zephyr();

    #ifdef TEST
    static const char *argv[] = {"test"};
    upytest_set_heap(heap, heap + sizeof(heap));
    int r = tinytest_main(1, argv, groups);
    printf("status: %d\n", r);
    #endif

soft_reset:
    #if MICROPY_ENABLE_GC
    gc_init(heap, heap + sizeof(heap));
    #endif
    mp_init();
    mp_obj_list_init(mp_sys_path, 0);
    mp_obj_list_append(mp_sys_path, MP_OBJ_NEW_QSTR(MP_QSTR_)); // current dir (or base dir of the script)
    mp_obj_list_init(mp_sys_argv, 0);

    #if MICROPY_MODULE_FROZEN
    pyexec_frozen_module("main.py");
    #endif

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

    printf("soft reboot\n");
    goto soft_reset;

    return 0;
}