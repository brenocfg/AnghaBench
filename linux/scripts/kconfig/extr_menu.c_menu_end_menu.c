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
struct TYPE_2__ {struct TYPE_2__* parent; int /*<<< orphan*/  next; } ;

/* Variables and functions */
 TYPE_1__* current_menu ; 
 int /*<<< orphan*/ * last_entry_ptr ; 

void menu_end_menu(void)
{
	last_entry_ptr = &current_menu->next;
	current_menu = current_menu->parent;
}