#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qstr ;
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_6__ {size_t alloc; TYPE_1__* table; } ;
typedef  TYPE_2__ mp_map_t ;
struct TYPE_7__ {TYPE_2__ map; } ;
struct TYPE_5__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_printf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_map_slot_is_filled (TYPE_2__*,size_t) ; 
 TYPE_3__* mp_obj_module_get_globals (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_str_get_qstr (int /*<<< orphan*/ ) ; 
 char* mp_obj_str_get_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_store_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mp_import_all(mp_obj_t module) {
    DEBUG_printf("import all %p\n", module);

    // TODO: Support __all__
    mp_map_t *map = &mp_obj_module_get_globals(module)->map;
    for (size_t i = 0; i < map->alloc; i++) {
        if (mp_map_slot_is_filled(map, i)) {
            // Entry in module global scope may be generated programmatically
            // (and thus be not a qstr for longer names). Avoid turning it in
            // qstr if it has '_' and was used exactly to save memory.
            const char *name = mp_obj_str_get_str(map->table[i].key);
            if (*name != '_') {
                qstr qname = mp_obj_str_get_qstr(map->table[i].key);
                mp_store_name(qname, map->table[i].value);
            }
        }
    }
}