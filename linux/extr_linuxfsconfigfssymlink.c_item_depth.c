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
 int /*<<< orphan*/  configfs_is_root (struct config_item*) ; 

__attribute__((used)) static int item_depth(struct config_item * item)
{
	struct config_item * p = item;
	int depth = 0;
	do { depth++; } while ((p = p->ci_parent) && !configfs_is_root(p));
	return depth;
}