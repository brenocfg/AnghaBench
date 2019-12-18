#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mp_uint_t ;
typedef  scalar_t__ mp_obj_t ;
typedef  scalar_t__ mp_int_t ;
struct TYPE_5__ {int /*<<< orphan*/  greyscale; } ;
typedef  TYPE_1__ microbit_image_obj_t ;

/* Variables and functions */
 scalar_t__ MAX_BRIGHTNESS ; 
 int /*<<< orphan*/  check_mutability (TYPE_1__*) ; 
 int /*<<< orphan*/  greyscaleSetPixelValue (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ imageHeight (TYPE_1__*) ; 
 scalar_t__ imageWidth (TYPE_1__*) ; 
 scalar_t__ mp_const_none ; 
 scalar_t__ mp_obj_get_int (scalar_t__ const) ; 
 int /*<<< orphan*/  mp_raise_ValueError (char*) ; 

mp_obj_t microbit_image_set_pixel(mp_uint_t n_args, const mp_obj_t *args) {
    (void)n_args;
    microbit_image_obj_t *self = (microbit_image_obj_t*)args[0];
    check_mutability(self);
    mp_int_t x = mp_obj_get_int(args[1]);
    mp_int_t y = mp_obj_get_int(args[2]);
    if (x < 0 || y < 0) {
        mp_raise_ValueError("index cannot be negative");
    }
    mp_int_t bright = mp_obj_get_int(args[3]);
    if (bright < 0 || bright > MAX_BRIGHTNESS)
        mp_raise_ValueError("brightness out of bounds.");
    if (x < imageWidth(self) && y < imageHeight(self)) {
        greyscaleSetPixelValue(&(self->greyscale), x, y, bright);
        return mp_const_none;
    }
    mp_raise_ValueError("index too large");
}