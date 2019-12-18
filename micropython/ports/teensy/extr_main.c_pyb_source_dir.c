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
 scalar_t__ mp_obj_is_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pyb_config_source_dir ; 

mp_obj_t pyb_source_dir(mp_obj_t source_dir) {
    if (mp_obj_is_str(source_dir)) {
        pyb_config_source_dir = source_dir;
    }
    return mp_const_none;
}