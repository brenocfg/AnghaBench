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
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  configfs_unregister_group (struct config_group*) ; 
 int /*<<< orphan*/  kfree (struct config_group*) ; 

void configfs_unregister_default_group(struct config_group *group)
{
	configfs_unregister_group(group);
	kfree(group);
}