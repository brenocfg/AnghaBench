#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mp_obj_t ;
typedef  scalar_t__ mp_int_t ;
struct TYPE_3__ {int /*<<< orphan*/  greyscale; } ;
typedef  TYPE_1__ microbit_image_obj_t ;

/* Variables and functions */
 scalar_t__ MAX_BRIGHTNESS ; 
 int /*<<< orphan*/  check_mutability (TYPE_1__*) ; 
 int /*<<< orphan*/  greyscaleFill (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ mp_const_none ; 
 scalar_t__ mp_obj_get_int (scalar_t__) ; 
 int /*<<< orphan*/  mp_raise_ValueError (char*) ; 

mp_obj_t microbit_image_fill(mp_obj_t self_in, mp_obj_t n_in) {
    microbit_image_obj_t *self = (microbit_image_obj_t*)self_in;
    check_mutability(self);
    mp_int_t n = mp_obj_get_int(n_in);
    if (n < 0 || n > MAX_BRIGHTNESS) {
        mp_raise_ValueError("brightness out of bounds.");
    }
    greyscaleFill(&self->greyscale, n);
    return mp_const_none;
}