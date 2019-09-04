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
struct menu {TYPE_2__* sym; TYPE_1__* prompt; } ;
struct TYPE_4__ {char const* name; } ;
struct TYPE_3__ {char const* text; } ;

/* Variables and functions */

const char *menu_get_prompt(struct menu *menu)
{
	if (menu->prompt)
		return menu->prompt->text;
	else if (menu->sym)
		return menu->sym->name;
	return NULL;
}