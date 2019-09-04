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
 int /*<<< orphan*/  mp_obj_new_str_via_qstr (char const*,size_t) ; 
 char* mp_obj_str_get_data (int /*<<< orphan*/ ,size_t*) ; 

mp_obj_t mp_obj_str_intern_checked(mp_obj_t obj) {
    size_t len;
    const char *data = mp_obj_str_get_data(obj, &len);
    return mp_obj_new_str_via_qstr((const char*)data, len);
}