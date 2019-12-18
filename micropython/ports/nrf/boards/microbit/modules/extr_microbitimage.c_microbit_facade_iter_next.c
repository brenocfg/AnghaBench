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
typedef  scalar_t__ mp_obj_t ;
struct TYPE_2__ {size_t index; scalar_t__ image; int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ facade_iterator_t ;

/* Variables and functions */
 scalar_t__ MP_OBJ_STOP_ITERATION ; 
 int /*<<< orphan*/  microbit_image_set_from_char (scalar_t__,char const) ; 
 char* mp_obj_str_get_data (int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static mp_obj_t microbit_facade_iter_next(mp_obj_t iter_in) {
    facade_iterator_t *iter = (facade_iterator_t *)iter_in;
    size_t len;
    const char *text = mp_obj_str_get_data(iter->string, &len);
    if (iter->index >= len) {
        return MP_OBJ_STOP_ITERATION;
    }
    microbit_image_set_from_char(iter->image, text[iter->index]);
    iter->index++;
    return iter->image;
}