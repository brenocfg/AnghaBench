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
struct menu {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 struct menu* current_entry ; 
 struct menu* current_menu ; 
 int /*<<< orphan*/ * last_entry_ptr ; 

struct menu *menu_add_menu(void)
{
	last_entry_ptr = &current_entry->list;
	return current_menu = current_entry;
}