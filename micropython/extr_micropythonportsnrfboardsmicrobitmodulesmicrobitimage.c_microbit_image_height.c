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

/* Variables and functions */
 scalar_t__ MP_OBJ_NEW_SMALL_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imageHeight (int /*<<< orphan*/ *) ; 

mp_obj_t microbit_image_height(mp_obj_t self_in) {
    microbit_image_obj_t *self = (microbit_image_obj_t*)self_in;
    return MP_OBJ_NEW_SMALL_INT(imageHeight(self));
}