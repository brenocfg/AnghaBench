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
typedef  int /*<<< orphan*/  mp_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_NEW_SMALL_INT (size_t) ; 
 scalar_t__ mp_obj_equal (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

mp_obj_t mp_seq_count_obj(const mp_obj_t *items, size_t len, mp_obj_t value) {
    size_t count = 0;
    for (size_t i = 0; i < len; i++) {
         if (mp_obj_equal(items[i], value)) {
              count++;
         }
    }

    // Common sense says this cannot overflow small int
    return MP_OBJ_NEW_SMALL_INT(count);
}