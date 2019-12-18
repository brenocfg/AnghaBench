#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct symbol {int type; char* name; } ;
struct TYPE_3__ {struct symbol* sym; } ;

/* Variables and functions */
 int S_UNKNOWN ; 
 TYPE_1__* current_entry ; 
 int /*<<< orphan*/  menu_warn (TYPE_1__*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_type_name (int) ; 

void menu_set_type(int type)
{
	struct symbol *sym = current_entry->sym;

	if (sym->type == type)
		return;
	if (sym->type == S_UNKNOWN) {
		sym->type = type;
		return;
	}
	menu_warn(current_entry,
		"ignoring type redefinition of '%s' from '%s' to '%s'",
		sym->name ? sym->name : "<choice>",
		sym_type_name(sym->type), sym_type_name(type));
}