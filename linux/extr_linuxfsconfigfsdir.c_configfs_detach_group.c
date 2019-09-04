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

/* Variables and functions */
 int /*<<< orphan*/  configfs_detach_item (struct config_item*) ; 
 int /*<<< orphan*/  detach_groups (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_config_group (struct config_item*) ; 

__attribute__((used)) static void configfs_detach_group(struct config_item *item)
{
	detach_groups(to_config_group(item));
	configfs_detach_item(item);
}