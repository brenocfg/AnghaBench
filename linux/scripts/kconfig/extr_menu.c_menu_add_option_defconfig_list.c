#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* sym; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYMBOL_NO_WRITE ; 
 TYPE_2__* current_entry ; 
 TYPE_1__* sym_defconfig_list ; 
 int /*<<< orphan*/  zconf_error (char*) ; 

void menu_add_option_defconfig_list(void)
{
	if (!sym_defconfig_list)
		sym_defconfig_list = current_entry->sym;
	else if (sym_defconfig_list != current_entry->sym)
		zconf_error("trying to redefine defconfig symbol");
	sym_defconfig_list->flags |= SYMBOL_NO_WRITE;
}