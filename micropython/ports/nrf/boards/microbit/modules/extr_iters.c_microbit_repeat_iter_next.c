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
struct TYPE_2__ {scalar_t__ index; int /*<<< orphan*/  iterable; } ;
typedef  TYPE_1__ repeat_iterator_t ;
typedef  scalar_t__ mp_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_NEW_SMALL_INT (scalar_t__) ; 
 int /*<<< orphan*/  MP_OBJ_SENTINEL ; 
 scalar_t__ mp_obj_get_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_len (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_subscr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mp_obj_t microbit_repeat_iter_next(mp_obj_t iter_in) {
    repeat_iterator_t *iter = (repeat_iterator_t *)iter_in;
    iter->index++;
    if (iter->index >= mp_obj_get_int(mp_obj_len(iter->iterable))) {
        iter->index = 0;
    }
    return mp_obj_subscr(iter->iterable, MP_OBJ_NEW_SMALL_INT(iter->index), MP_OBJ_SENTINEL);
}