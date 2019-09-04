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
 scalar_t__ IS_ERR_OR_NULL (struct config_group*) ; 
 int /*<<< orphan*/  configfs_unregister_default_group (struct config_group*) ; 

void pci_ep_cfs_remove_epf_group(struct config_group *group)
{
	if (IS_ERR_OR_NULL(group))
		return;

	configfs_unregister_default_group(group);
}