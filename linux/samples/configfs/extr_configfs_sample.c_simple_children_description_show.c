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
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t simple_children_description_show(struct config_item *item,
		char *page)
{
	return sprintf(page,
"[02-simple-children]\n"
"\n"
"This subsystem allows the creation of child config_items.  These\n"
"items have only one attribute that is readable and writeable.\n");
}