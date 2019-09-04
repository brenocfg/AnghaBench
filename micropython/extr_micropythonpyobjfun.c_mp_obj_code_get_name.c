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
typedef  int /*<<< orphan*/  qstr ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/ * mp_decode_uint_skip (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mp_decode_uint_value (int /*<<< orphan*/  const*) ; 

qstr mp_obj_code_get_name(const byte *code_info) {
    code_info = mp_decode_uint_skip(code_info); // skip code_info_size entry
    #if MICROPY_PERSISTENT_CODE
    return code_info[0] | (code_info[1] << 8);
    #else
    return mp_decode_uint_value(code_info);
    #endif
}