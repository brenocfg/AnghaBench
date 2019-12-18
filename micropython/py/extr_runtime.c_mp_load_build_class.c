#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ mp_map_elem_t ;
struct TYPE_5__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_OP_printf (char*) ; 
 int /*<<< orphan*/  MP_MAP_LOOKUP ; 
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP_OBJ_NEW_QSTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_QSTR___build_class__ ; 
 TYPE_3__* MP_STATE_VM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_builtin___build_class___obj ; 
 TYPE_1__* mp_map_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_module_builtins_override_dict ; 

mp_obj_t mp_load_build_class(void) {
    DEBUG_OP_printf("load_build_class\n");
    #if MICROPY_CAN_OVERRIDE_BUILTINS
    if (MP_STATE_VM(mp_module_builtins_override_dict) != NULL) {
        // lookup in additional dynamic table of builtins first
        mp_map_elem_t *elem = mp_map_lookup(&MP_STATE_VM(mp_module_builtins_override_dict)->map, MP_OBJ_NEW_QSTR(MP_QSTR___build_class__), MP_MAP_LOOKUP);
        if (elem != NULL) {
            return elem->value;
        }
    }
    #endif
    return MP_OBJ_FROM_PTR(&mp_builtin___build_class___obj);
}