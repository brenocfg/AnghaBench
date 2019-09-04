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
 int /*<<< orphan*/  configfs_remove_dir (struct config_item*) ; 
 int /*<<< orphan*/  detach_attrs (struct config_item*) ; 

__attribute__((used)) static void configfs_detach_item(struct config_item *item)
{
	detach_attrs(item);
	configfs_remove_dir(item);
}