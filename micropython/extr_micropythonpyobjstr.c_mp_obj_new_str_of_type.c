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
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  mp_obj_new_bytes (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  mp_obj_new_str (char const*,size_t) ; 
 int /*<<< orphan*/  const mp_type_str ; 

mp_obj_t mp_obj_new_str_of_type(const mp_obj_type_t *type, const byte* data, size_t len) {
    if (type == &mp_type_str) {
        return mp_obj_new_str((const char*)data, len);
    } else {
        return mp_obj_new_bytes(data, len);
    }
}