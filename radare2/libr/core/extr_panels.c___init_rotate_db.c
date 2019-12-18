#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* panels; } ;
struct TYPE_4__ {int /*<<< orphan*/  rotate_db; } ;
typedef  TYPE_1__ RPanels ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 char* PANEL_CMD_HEXDUMP ; 
 int /*<<< orphan*/  __rotate_disasm_cb ; 
 int /*<<< orphan*/  __rotate_entropy_h_cb ; 
 int /*<<< orphan*/  __rotate_entropy_v_cb ; 
 int /*<<< orphan*/  __rotate_function_cb ; 
 int /*<<< orphan*/  __rotate_hexdump_cb ; 
 int /*<<< orphan*/  __rotate_register_cb ; 
 int /*<<< orphan*/  sdb_ptr_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void __init_rotate_db(RCore *core) {
	RPanels *panels = core->panels;
	sdb_ptr_set (panels->rotate_db, "pd", &__rotate_disasm_cb, 0);
	sdb_ptr_set (panels->rotate_db, "p==", &__rotate_entropy_h_cb, 0);
	sdb_ptr_set (panels->rotate_db, "p=", &__rotate_entropy_v_cb, 0);
	sdb_ptr_set (panels->rotate_db, "px", &__rotate_hexdump_cb, 0);
	sdb_ptr_set (panels->rotate_db, "dr", &__rotate_register_cb, 0);
	sdb_ptr_set (panels->rotate_db, "af", &__rotate_function_cb, 0);
	sdb_ptr_set (panels->rotate_db, PANEL_CMD_HEXDUMP, &__rotate_hexdump_cb, 0);
}