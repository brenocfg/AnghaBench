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
 scalar_t__ data ; 
 int /*<<< orphan*/  len ; 
 int /*<<< orphan*/  mp_obj_new_str_via_qstr (char const*,int /*<<< orphan*/ ) ; 

mp_obj_t mp_obj_str_intern(mp_obj_t str) {
    GET_STR_DATA_LEN(str, data, len);
    return mp_obj_new_str_via_qstr((const char*)data, len);
}