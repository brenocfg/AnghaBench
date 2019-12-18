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
typedef  scalar_t__ qstr ;
typedef  int /*<<< orphan*/  mp_obj_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_NEW_QSTR (scalar_t__) ; 
 scalar_t__ MP_QSTRnull ; 
 int /*<<< orphan*/  mp_obj_new_str_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  mp_type_str ; 
 scalar_t__ qstr_find_strn (char const*,size_t) ; 

mp_obj_t mp_obj_new_str(const char* data, size_t len) {
    qstr q = qstr_find_strn(data, len);
    if (q != MP_QSTRnull) {
        // qstr with this data already exists
        return MP_OBJ_NEW_QSTR(q);
    } else {
        // no existing qstr, don't make one
        return mp_obj_new_str_copy(&mp_type_str, (const byte*)data, len);
    }
}