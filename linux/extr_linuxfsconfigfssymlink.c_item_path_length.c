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
struct config_item {struct config_item* ci_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_item_name (struct config_item*) ; 
 int /*<<< orphan*/  configfs_is_root (struct config_item*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int item_path_length(struct config_item * item)
{
	struct config_item * p = item;
	int length = 1;
	do {
		length += strlen(config_item_name(p)) + 1;
		p = p->ci_parent;
	} while (p && !configfs_is_root(p));
	return length;
}