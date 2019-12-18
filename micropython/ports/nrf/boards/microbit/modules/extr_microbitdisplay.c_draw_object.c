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
typedef  scalar_t__ mp_obj_t ;
typedef  int /*<<< orphan*/  microbit_image_obj_t ;
typedef  int /*<<< orphan*/  microbit_display_obj_t ;
typedef  int /*<<< orphan*/  MP_STATE_VM ;

/* Variables and functions */
 int /*<<< orphan*/ * BLANK_IMAGE ; 
 scalar_t__ MP_OBJ_STOP_ITERATION ; 
 scalar_t__* MP_STATE_PORT (int /*<<< orphan*/ ) ; 
 int async_clear ; 
 int /*<<< orphan*/  async_data ; 
 int /*<<< orphan*/  async_stop () ; 
 int /*<<< orphan*/  microbit_display_obj ; 
 int /*<<< orphan*/  microbit_display_show (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * microbit_image_for_char (char const) ; 
 int /*<<< orphan*/  microbit_image_type ; 
 int /*<<< orphan*/ * mp_obj_get_type (scalar_t__) ; 
 scalar_t__ mp_obj_is_str (scalar_t__) ; 
 int /*<<< orphan*/  mp_obj_new_exception_msg (int /*<<< orphan*/ *,char*) ; 
 char* mp_obj_str_get_data (scalar_t__,size_t*) ; 
 int /*<<< orphan*/  mp_type_TypeError ; 

__attribute__((used)) static void draw_object(mp_obj_t obj) {
    microbit_display_obj_t *display = (microbit_display_obj_t*)MP_STATE_PORT(async_data)[0];
    if (obj == MP_OBJ_STOP_ITERATION) {
        if (async_clear) {
            microbit_display_show(&microbit_display_obj, BLANK_IMAGE);
            async_clear = false;
        } else {
            async_stop();
        }
    } else if (mp_obj_get_type(obj) == &microbit_image_type) {
        microbit_display_show(display, (microbit_image_obj_t *)obj);
    } else if (mp_obj_is_str(obj)) {
        size_t len;
        const char *str = mp_obj_str_get_data(obj, &len);
        if (len == 1) {
            microbit_display_show(display, microbit_image_for_char(str[0]));
        } else {
            async_stop();
        }
    } else {
        MP_STATE_VM(mp_pending_exception) = mp_obj_new_exception_msg(&mp_type_TypeError, "not an image.");
        async_stop();
    }
}