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
 int /*<<< orphan*/  GET_STR_DATA_LEN (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bad_implicit_conversion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l ; 
 scalar_t__ mp_obj_is_str_or_bytes (int /*<<< orphan*/ ) ; 
 scalar_t__ s ; 

const char *mp_obj_str_get_str(mp_obj_t self_in) {
    if (mp_obj_is_str_or_bytes(self_in)) {
        GET_STR_DATA_LEN(self_in, s, l);
        (void)l; // len unused
        return (const char*)s;
    } else {
        bad_implicit_conversion(self_in);
    }
}