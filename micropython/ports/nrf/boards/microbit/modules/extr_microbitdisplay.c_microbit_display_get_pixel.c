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
typedef  int mp_int_t ;
struct TYPE_3__ {int** image_buffer; } ;
typedef  TYPE_1__ microbit_display_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  mp_raise_ValueError (char*) ; 

mp_int_t microbit_display_get_pixel(microbit_display_obj_t *display, mp_int_t x, mp_int_t y) {
    if (x < 0 || y < 0 || x > 4 || y > 4) {
        mp_raise_ValueError("index out of bounds.");
    }
    return display->image_buffer[x][y];
}