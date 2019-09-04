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
typedef  int /*<<< orphan*/  vstr_t ;

/* Variables and functions */
 scalar_t__ HEAP_END ; 
 int /*<<< orphan*/  LED_BUILTIN ; 
 int /*<<< orphan*/  MP_OBJ_NEW_QSTR (int /*<<< orphan*/ ) ; 
 scalar_t__ MP_OBJ_NULL ; 
 int /*<<< orphan*/  MP_QSTR_ ; 
 int /*<<< orphan*/  OUTPUT ; 
 int /*<<< orphan*/  PYB_LED_BUILTIN ; 
 scalar_t__ PYEXEC_MODE_RAW_REPL ; 
 int SCB_CCR ; 
 int /*<<< orphan*/  _heap_start ; 
 int /*<<< orphan*/  flash_error (int) ; 
 int /*<<< orphan*/  gc_init (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  led_init () ; 
 int /*<<< orphan*/  led_state (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_init () ; 
 int /*<<< orphan*/  mp_obj_list_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_list_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* mp_obj_str_get_str (scalar_t__) ; 
 int /*<<< orphan*/  mp_stack_ctrl_init () ; 
 int /*<<< orphan*/  mp_stack_set_limit (int) ; 
 int /*<<< orphan*/  mp_sys_argv ; 
 int /*<<< orphan*/  mp_sys_path ; 
 int /*<<< orphan*/  pinMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pin_init0 () ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ pyb_config_main ; 
 int /*<<< orphan*/  pyexec_file_if_exists (char*) ; 
 scalar_t__ pyexec_friendly_repl () ; 
 scalar_t__ pyexec_mode_kind ; 
 scalar_t__ pyexec_raw_repl () ; 
 int /*<<< orphan*/  readline_init0 () ; 
 int /*<<< orphan*/  vstr_add_str (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vstr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vstr_new (int) ; 
 char* vstr_null_terminated_str (int /*<<< orphan*/ *) ; 

int main(void) {
    // TODO: Put this in a more common initialization function.
    // Turn on STKALIGN which keeps the stack 8-byte aligned for interrupts
    // (per EABI)
    #define SCB_CCR_STKALIGN (1 << 9)
    SCB_CCR |= SCB_CCR_STKALIGN;

    mp_stack_ctrl_init();
    mp_stack_set_limit(10240);

    pinMode(LED_BUILTIN, OUTPUT);
    led_init();

//    int first_soft_reset = true;

soft_reset:

    led_state(PYB_LED_BUILTIN, 1);

    // GC init
    gc_init(&_heap_start, (void*)HEAP_END);

    // MicroPython init
    mp_init();
    mp_obj_list_init(mp_sys_path, 0);
    mp_obj_list_append(mp_sys_path, MP_OBJ_NEW_QSTR(MP_QSTR_)); // current dir (or base dir of the script)
    mp_obj_list_init(mp_sys_argv, 0);

    readline_init0();

    pin_init0();

#if 0
    // add some functions to the python namespace
    {
        mp_store_name(MP_QSTR_help, mp_make_function_n(0, pyb_help));
        mp_obj_t m = mp_obj_new_module(MP_QSTR_pyb);
        mp_store_attr(m, MP_QSTR_info, mp_make_function_n(0, pyb_info));
        mp_store_attr(m, MP_QSTR_source_dir, mp_make_function_n(1, pyb_source_dir));
        mp_store_attr(m, MP_QSTR_main, mp_make_function_n(1, pyb_main));
        mp_store_attr(m, MP_QSTR_gc, mp_make_function_n(0, pyb_gc));
        mp_store_attr(m, MP_QSTR_delay, mp_make_function_n(1, pyb_delay));
        mp_store_attr(m, MP_QSTR_led, mp_make_function_n(1, pyb_led));
        mp_store_attr(m, MP_QSTR_LED, (mp_obj_t)&pyb_led_type);
        mp_store_attr(m, MP_QSTR_analogRead, mp_make_function_n(1, pyb_analog_read));
        mp_store_attr(m, MP_QSTR_analogWrite, mp_make_function_n(2, pyb_analog_write));
        mp_store_attr(m, MP_QSTR_analogWriteResolution, mp_make_function_n(1, pyb_analog_write_resolution));
        mp_store_attr(m, MP_QSTR_analogWriteFrequency, mp_make_function_n(2, pyb_analog_write_frequency));

        mp_store_attr(m, MP_QSTR_gpio, (mp_obj_t)&pyb_gpio_obj);
        mp_store_attr(m, MP_QSTR_Servo, mp_make_function_n(0, pyb_Servo));
        mp_store_name(MP_QSTR_pyb, m);
    }
#endif

#if MICROPY_MODULE_FROZEN
    pyexec_frozen_module("boot.py");
#else
    if (!pyexec_file_if_exists("/boot.py")) {
        flash_error(4);
    }
#endif

    // Turn bootup LED off
    led_state(PYB_LED_BUILTIN, 0);

    // run main script
#if MICROPY_MODULE_FROZEN
    pyexec_frozen_module("main.py");
#else
    {
        vstr_t *vstr = vstr_new(16);
        vstr_add_str(vstr, "/");
        if (pyb_config_main == MP_OBJ_NULL) {
            vstr_add_str(vstr, "main.py");
        } else {
            vstr_add_str(vstr, mp_obj_str_get_str(pyb_config_main));
        }
        if (!pyexec_file_if_exists(vstr_null_terminated_str(vstr))) {
            flash_error(3);
        }
        vstr_free(vstr);
    }
#endif

    // enter REPL
    // REPL mode can change, or it can request a soft reset
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

    printf("MPY: soft reboot\n");

//    first_soft_reset = false;
    goto soft_reset;
}