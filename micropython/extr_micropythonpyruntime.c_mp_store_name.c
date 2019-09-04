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
typedef  int /*<<< orphan*/  mp_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_OP_printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_OBJ_NEW_QSTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_locals_get () ; 
 int /*<<< orphan*/  mp_obj_dict_store (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qstr_str (int /*<<< orphan*/ ) ; 

void mp_store_name(qstr qst, mp_obj_t obj) {
    DEBUG_OP_printf("store name %s <- %p\n", qstr_str(qst), obj);
    mp_obj_dict_store(MP_OBJ_FROM_PTR(mp_locals_get()), MP_OBJ_NEW_QSTR(qst), obj);
}