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
 int /*<<< orphan*/  MICROPY_PORT_DEINIT_FUNC ; 
 int /*<<< orphan*/  MP_THREAD_GIL_EXIT () ; 

void mp_deinit(void) {
    MP_THREAD_GIL_EXIT();

    //mp_obj_dict_free(&dict_main);
    //mp_map_deinit(&MP_STATE_VM(mp_loaded_modules_map));

    // call port specific deinitialization if any
#ifdef MICROPY_PORT_DEINIT_FUNC
    MICROPY_PORT_DEINIT_FUNC;
#endif
}