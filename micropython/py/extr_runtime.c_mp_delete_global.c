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

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_OP_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_OBJ_NEW_QSTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_globals_get () ; 
 int /*<<< orphan*/  mp_obj_dict_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qstr_str (int /*<<< orphan*/ ) ; 

void mp_delete_global(qstr qst) {
    DEBUG_OP_printf("delete global %s\n", qstr_str(qst));
    // TODO convert KeyError to NameError if qst not found
    mp_obj_dict_delete(MP_OBJ_FROM_PTR(mp_globals_get()), MP_OBJ_NEW_QSTR(qst));
}