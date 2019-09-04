#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* make_new ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  MP_STATE_PORT ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP_OBJ_NEW_QSTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_OBJ_NEW_SMALL_INT (int) ; 
 int /*<<< orphan*/  MP_QSTR_ ; 
 scalar_t__ PYEXEC_MODE_RAW_REPL ; 
 int /*<<< orphan*/  _heap_end ; 
 int /*<<< orphan*/  _heap_start ; 
 int /*<<< orphan*/  _ram_end ; 
 int /*<<< orphan*/  gc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ machine_hard_uart_type ; 
 int /*<<< orphan*/  machine_init () ; 
 int /*<<< orphan*/  mp_deinit () ; 
 int /*<<< orphan*/  mp_init () ; 
 int /*<<< orphan*/  mp_obj_list_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_list_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_stack_set_limit (int) ; 
 int /*<<< orphan*/  mp_stack_set_top (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_sys_argv ; 
 int /*<<< orphan*/  mp_sys_path ; 
 int /*<<< orphan*/  pin_init0 () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  pyb_set_repl_info (int /*<<< orphan*/ ) ; 
 int pyexec_friendly_repl () ; 
 scalar_t__ pyexec_mode_kind ; 
 scalar_t__ pyexec_raw_repl () ; 
 int /*<<< orphan*/  readline_init0 () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int main(int argc, char **argv) {
    
soft_reset:
    mp_stack_set_top(&_ram_end);

    // Stack limit should be less than real stack size, so we have a chance
    // to recover from limit hit.  (Limit is measured in bytes.)
    mp_stack_set_limit((char*)&_ram_end - (char*)&_heap_end - 400);

    machine_init();

    gc_init(&_heap_start, &_heap_end);

    mp_init();
    mp_obj_list_init(mp_sys_path, 0);
    mp_obj_list_append(mp_sys_path, MP_OBJ_NEW_QSTR(MP_QSTR_)); // current dir (or base dir of the script)
    mp_obj_list_init(mp_sys_argv, 0);

    pyb_set_repl_info(MP_OBJ_NEW_SMALL_INT(0));

    readline_init0();

#if MICROPY_PY_MACHINE_HW_SPI
    spi_init0();
#endif

#if MICROPY_PY_MACHINE_I2C
    i2c_init0();
#endif

#if MICROPY_PY_MACHINE_ADC
    adc_init0();
#endif

#if MICROPY_PY_MACHINE_HW_PWM
    pwm_init0();
#endif

#if MICROPY_PY_MACHINE_RTCOUNTER
    rtc_init0();
#endif

#if MICROPY_PY_MACHINE_TIMER
    timer_init0();
#endif

#if MICROPY_PY_MACHINE_UART
    uart_init0();
#endif

#if (MICROPY_PY_BLE_NUS == 0)
    {
        mp_obj_t args[2] = {
            MP_OBJ_NEW_SMALL_INT(0),
            MP_OBJ_NEW_SMALL_INT(115200),
        };
        MP_STATE_PORT(board_stdio_uart) = machine_hard_uart_type.make_new((mp_obj_t)&machine_hard_uart_type, MP_ARRAY_SIZE(args), 0, args);
    }
#endif

pin_init0();

#if MICROPY_MBFS
    microbit_filesystem_init();
#endif

#if MICROPY_HW_HAS_SDCARD
    // if an SD card is present then mount it on /sd/
    if (sdcard_is_present()) {
        // create vfs object
        fs_user_mount_t *vfs = m_new_obj_maybe(fs_user_mount_t);
        if (vfs == NULL) {
            goto no_mem_for_sd;
        }
        vfs->str = "/sd";
        vfs->len = 3;
        vfs->flags = FSUSER_FREE_OBJ;
        sdcard_init_vfs(vfs);

        // put the sd device in slot 1 (it will be unused at this point)
        MP_STATE_PORT(fs_user_mount)[1] = vfs;

        FRESULT res = f_mount(&vfs->fatfs, vfs->str, 1);
        if (res != FR_OK) {
            printf("MPY: can't mount SD card\n");
            MP_STATE_PORT(fs_user_mount)[1] = NULL;
            m_del_obj(fs_user_mount_t, vfs);
        } else {
            // TODO these should go before the /flash entries in the path
            mp_obj_list_append(mp_sys_path, MP_OBJ_NEW_QSTR(MP_QSTR__slash_sd));
            mp_obj_list_append(mp_sys_path, MP_OBJ_NEW_QSTR(MP_QSTR__slash_sd_slash_lib));

			// use SD card as current directory
			f_chdrive("/sd");
        }
        no_mem_for_sd:;
    }
#endif

#if (MICROPY_HW_HAS_LED)
    led_init();

    do_str("import board\r\n" \
           "board.LED(1).on()",
           MP_PARSE_FILE_INPUT);
#endif

    // Main script is finished, so now go into REPL mode.
    // The REPL mode can change, or it can request a soft reset.
    int ret_code = 0;

#if MICROPY_PY_BLE_NUS
    ble_uart_init0();
#endif

#if MICROPY_PY_MACHINE_SOFT_PWM
    ticker_init0();
    softpwm_init0();
#endif

#if MICROPY_PY_MUSIC
    microbit_music_init0();
#endif
#if BOARD_SPECIFIC_MODULES
    board_modules_init0();
#endif

#if MICROPY_PY_MACHINE_SOFT_PWM
    ticker_start();
    pwm_start();
#endif

#if MICROPY_VFS || MICROPY_MBFS
    // run boot.py and main.py if they exist.
    pyexec_file_if_exists("boot.py");
    pyexec_file_if_exists("main.py");
#endif

    for (;;) {
        if (pyexec_mode_kind == PYEXEC_MODE_RAW_REPL) {
            if (pyexec_raw_repl() != 0) {
                break;
            }
        } else {
            ret_code = pyexec_friendly_repl();
            if (ret_code != 0) {
                break;
            }
        }
    }

    mp_deinit();

    printf("MPY: soft reboot\n");

#if BLUETOOTH_SD
    sd_softdevice_disable();
#endif

    goto soft_reset;

    return 0;
}