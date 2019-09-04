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
typedef  scalar_t__ mp_int_t ;
typedef  int /*<<< orphan*/  microbit_image_obj_t ;

/* Variables and functions */
 scalar_t__ MP_OBJ_NEW_SMALL_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imageGetPixelValue (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ imageHeight (int /*<<< orphan*/ *) ; 
 scalar_t__ imageWidth (int /*<<< orphan*/ *) ; 
 scalar_t__ mp_obj_get_int (scalar_t__) ; 
 int /*<<< orphan*/  mp_raise_ValueError (char*) ; 

mp_obj_t microbit_image_get_pixel(mp_obj_t self_in, mp_obj_t x_in, mp_obj_t y_in) {
    microbit_image_obj_t *self = (microbit_image_obj_t*)self_in;
    mp_int_t x = mp_obj_get_int(x_in);
    mp_int_t y = mp_obj_get_int(y_in);
    if (x < 0 || y < 0) {
        mp_raise_ValueError("index cannot be negative");
    }
    if (x < imageWidth(self) && y < imageHeight(self)) {
        return MP_OBJ_NEW_SMALL_INT(imageGetPixelValue(self, x, y));
    }
    mp_raise_ValueError("index too large");
}