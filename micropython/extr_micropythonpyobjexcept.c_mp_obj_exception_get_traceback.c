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
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_3__ {size_t* traceback_data; size_t traceback_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_NATIVE_EXCEPTION (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* self ; 

void mp_obj_exception_get_traceback(mp_obj_t self_in, size_t *n, size_t **values) {
    GET_NATIVE_EXCEPTION(self, self_in);

    if (self->traceback_data == NULL) {
        *n = 0;
        *values = NULL;
    } else {
        *n = self->traceback_len;
        *values = self->traceback_data;
    }
}