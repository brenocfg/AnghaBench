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
 int /*<<< orphan*/  mp_const_none ; 
 int /*<<< orphan*/  mp_obj_get_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repl_display_debugging_info ; 

mp_obj_t pyb_set_repl_info(mp_obj_t o_value) {
    repl_display_debugging_info = mp_obj_get_int(o_value);
    return mp_const_none;
}