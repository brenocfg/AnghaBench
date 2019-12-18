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
typedef  int /*<<< orphan*/  vprintf_like_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
#define  ESP_SPIRAM_SIZE_16MBITS 130 
#define  ESP_SPIRAM_SIZE_32MBITS 129 
#define  ESP_SPIRAM_SIZE_64MBITS 128 
 int /*<<< orphan*/  MALLOC_CAP_8BIT ; 
 int /*<<< orphan*/  MP_OBJ_NEW_QSTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_QSTR_ ; 
 int /*<<< orphan*/  MP_QSTR__slash_lib ; 
 int /*<<< orphan*/  MP_TASK_STACK_LEN ; 
 scalar_t__ MP_TASK_STACK_SIZE ; 
 scalar_t__ PYEXEC_MODE_FRIENDLY_REPL ; 
 scalar_t__ PYEXEC_MODE_RAW_REPL ; 
 int /*<<< orphan*/  esp_log_set_vprintf (int /*<<< orphan*/ ) ; 
 int esp_spiram_get_chip_size () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_init (void*,void*) ; 
 int /*<<< orphan*/  gc_sweep_all () ; 
 int /*<<< orphan*/  get_sp () ; 
 size_t heap_caps_get_largest_free_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_pins_deinit () ; 
 int /*<<< orphan*/  machine_pins_init () ; 
 int /*<<< orphan*/  machine_timer_deinit_all () ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  mp_deinit () ; 
 int /*<<< orphan*/  mp_hal_stdout_tx_str (char*) ; 
 int /*<<< orphan*/  mp_init () ; 
 int /*<<< orphan*/  mp_obj_list_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_list_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_stack_set_limit (scalar_t__) ; 
 int /*<<< orphan*/  mp_stack_set_top (void*) ; 
 int /*<<< orphan*/  mp_sys_argv ; 
 int /*<<< orphan*/  mp_sys_path ; 
 int /*<<< orphan*/  mp_thread_deinit () ; 
 int /*<<< orphan*/  mp_thread_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxTaskGetStackStart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pyexec_file_if_exists (char*) ; 
 scalar_t__ pyexec_friendly_repl () ; 
 int /*<<< orphan*/  pyexec_frozen_module (char*) ; 
 scalar_t__ pyexec_mode_kind ; 
 scalar_t__ pyexec_raw_repl () ; 
 int /*<<< orphan*/  readline_init0 () ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  uart_init () ; 
 int /*<<< orphan*/  usocket_events_deinit () ; 
 int /*<<< orphan*/  vprintf_null ; 

void mp_task(void *pvParameter) {
    volatile uint32_t sp = (uint32_t)get_sp();
    #if MICROPY_PY_THREAD
    mp_thread_init(pxTaskGetStackStart(NULL), MP_TASK_STACK_LEN);
    #endif
    uart_init();

    // TODO: CONFIG_SPIRAM_SUPPORT is for 3.3 compatibility, remove after move to 4.0.
    #if CONFIG_ESP32_SPIRAM_SUPPORT || CONFIG_SPIRAM_SUPPORT
    // Try to use the entire external SPIRAM directly for the heap
    size_t mp_task_heap_size;
    void *mp_task_heap = (void*)0x3f800000;
    switch (esp_spiram_get_chip_size()) {
        case ESP_SPIRAM_SIZE_16MBITS:
            mp_task_heap_size = 2 * 1024 * 1024;
            break;
        case ESP_SPIRAM_SIZE_32MBITS:
        case ESP_SPIRAM_SIZE_64MBITS:
            mp_task_heap_size = 4 * 1024 * 1024;
            break;
        default:
            // No SPIRAM, fallback to normal allocation
            mp_task_heap_size = heap_caps_get_largest_free_block(MALLOC_CAP_8BIT);
            mp_task_heap = malloc(mp_task_heap_size);
            break;
    }
    #else
    // Allocate the uPy heap using malloc and get the largest available region
    size_t mp_task_heap_size = heap_caps_get_largest_free_block(MALLOC_CAP_8BIT);
    void *mp_task_heap = malloc(mp_task_heap_size);
    #endif

soft_reset:
    // initialise the stack pointer for the main thread
    mp_stack_set_top((void *)sp);
    mp_stack_set_limit(MP_TASK_STACK_SIZE - 1024);
    gc_init(mp_task_heap, mp_task_heap + mp_task_heap_size);
    mp_init();
    mp_obj_list_init(mp_sys_path, 0);
    mp_obj_list_append(mp_sys_path, MP_OBJ_NEW_QSTR(MP_QSTR_));
    mp_obj_list_append(mp_sys_path, MP_OBJ_NEW_QSTR(MP_QSTR__slash_lib));
    mp_obj_list_init(mp_sys_argv, 0);
    readline_init0();

    // initialise peripherals
    machine_pins_init();

    // run boot-up scripts
    pyexec_frozen_module("_boot.py");
    pyexec_file_if_exists("boot.py");
    if (pyexec_mode_kind == PYEXEC_MODE_FRIENDLY_REPL) {
        pyexec_file_if_exists("main.py");
    }

    for (;;) {
        if (pyexec_mode_kind == PYEXEC_MODE_RAW_REPL) {
            vprintf_like_t vprintf_log = esp_log_set_vprintf(vprintf_null);
            if (pyexec_raw_repl() != 0) {
                break;
            }
            esp_log_set_vprintf(vprintf_log);
        } else {
            if (pyexec_friendly_repl() != 0) {
                break;
            }
        }
    }

    machine_timer_deinit_all();

    #if MICROPY_PY_THREAD
    mp_thread_deinit();
    #endif

    gc_sweep_all();

    mp_hal_stdout_tx_str("MPY: soft reboot\r\n");

    // deinitialise peripherals
    machine_pins_deinit();
    usocket_events_deinit();

    mp_deinit();
    fflush(stdout);
    goto soft_reset;
}