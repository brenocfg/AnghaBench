#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qstr ;
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_5__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ mp_map_elem_t ;
struct TYPE_6__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_OP_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_MAP_LOOKUP ; 
 int /*<<< orphan*/  MP_OBJ_NEW_QSTR (int /*<<< orphan*/ ) ; 
 TYPE_3__* mp_globals_get () ; 
 int /*<<< orphan*/  mp_load_global (int /*<<< orphan*/ ) ; 
 TYPE_3__* mp_locals_get () ; 
 TYPE_1__* mp_map_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qstr_str (int /*<<< orphan*/ ) ; 

mp_obj_t mp_load_name(qstr qst) {
    // logic: search locals, globals, builtins
    DEBUG_OP_printf("load name %s\n", qstr_str(qst));
    // If we're at the outer scope (locals == globals), dispatch to load_global right away
    if (mp_locals_get() != mp_globals_get()) {
        mp_map_elem_t *elem = mp_map_lookup(&mp_locals_get()->map, MP_OBJ_NEW_QSTR(qst), MP_MAP_LOOKUP);
        if (elem != NULL) {
            return elem->value;
        }
    }
    return mp_load_global(qst);
}