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
typedef  int /*<<< orphan*/  mp_uint_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
typedef  int /*<<< orphan*/  mp_buffer_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  mp_get_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_raise_TypeError (char*) ; 

void mp_get_buffer_raise(mp_obj_t obj, mp_buffer_info_t *bufinfo, mp_uint_t flags) {
    if (!mp_get_buffer(obj, bufinfo, flags)) {
        mp_raise_TypeError("object with buffer protocol required");
    }
}