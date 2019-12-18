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
typedef  int /*<<< orphan*/  mp_obj_type_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_NEW_SMALL_INT (size_t) ; 
 size_t mp_get_index (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const,int) ; 
 scalar_t__ mp_obj_equal (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mp_obj_get_type (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  mp_raise_ValueError (char*) ; 

mp_obj_t mp_seq_index_obj(const mp_obj_t *items, size_t len, size_t n_args, const mp_obj_t *args) {
    mp_obj_type_t *type = mp_obj_get_type(args[0]);
    mp_obj_t value = args[1];
    size_t start = 0;
    size_t stop = len;

    if (n_args >= 3) {
        start = mp_get_index(type, len, args[2], true);
        if (n_args >= 4) {
            stop = mp_get_index(type, len, args[3], true);
        }
    }

    for (size_t i = start; i < stop; i++) {
        if (mp_obj_equal(items[i], value)) {
            // Common sense says this cannot overflow small int
            return MP_OBJ_NEW_SMALL_INT(i);
        }
    }

    mp_raise_ValueError("object not in sequence");
}