#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct symbol {struct property* prop; int /*<<< orphan*/  flags; } ;
struct property {TYPE_1__* menu; struct property* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_CHANGED ; 
 int /*<<< orphan*/  SYMBOL_CHANGED ; 

__attribute__((used)) static void sym_set_changed(struct symbol *sym)
{
	struct property *prop;

	sym->flags |= SYMBOL_CHANGED;
	for (prop = sym->prop; prop; prop = prop->next) {
		if (prop->menu)
			prop->menu->flags |= MENU_CHANGED;
	}
}