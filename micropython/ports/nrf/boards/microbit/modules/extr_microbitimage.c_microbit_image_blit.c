#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int mp_uint_t ;
typedef  scalar_t__ mp_obj_t ;
typedef  scalar_t__ mp_int_t ;
struct TYPE_4__ {int /*<<< orphan*/  greyscale; } ;
typedef  TYPE_1__ microbit_image_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  check_mutability (TYPE_1__*) ; 
 int /*<<< orphan*/  image_blit (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  microbit_image_type ; 
 scalar_t__ mp_const_none ; 
 scalar_t__ mp_obj_get_int (scalar_t__ const) ; 
 int /*<<< orphan*/ * mp_obj_get_type (scalar_t__) ; 
 int /*<<< orphan*/  mp_raise_ValueError (char*) ; 
 int /*<<< orphan*/  mp_raise_msg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mp_type_TypeError ; 

mp_obj_t microbit_image_blit(mp_uint_t n_args, const mp_obj_t *args) {
    microbit_image_obj_t *self = (microbit_image_obj_t*)args[0];
    check_mutability(self);

    mp_obj_t src = args[1];
    if (mp_obj_get_type(src) != &microbit_image_type) {
        mp_raise_msg(&mp_type_TypeError, "expecting an image");
    }
    if (n_args == 7) {
        mp_raise_msg(&mp_type_TypeError, "must specify both offsets");
    }
    mp_int_t x = mp_obj_get_int(args[2]);
    mp_int_t y = mp_obj_get_int(args[3]);
    mp_int_t w = mp_obj_get_int(args[4]);
    mp_int_t h = mp_obj_get_int(args[5]);
    if (w < 0 || h < 0) {
        mp_raise_ValueError("size cannot be negative");
    }
    mp_int_t xdest;
    mp_int_t ydest;
    if (n_args == 6) {
        xdest = 0;
        ydest = 0;
    } else {
        xdest = mp_obj_get_int(args[6]);
        ydest = mp_obj_get_int(args[7]);
    }
    image_blit((microbit_image_obj_t *)src, &(self->greyscale), x, y, w, h, xdest, ydest);
    return mp_const_none;
}