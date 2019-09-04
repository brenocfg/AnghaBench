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
 scalar_t__ IS_ERR (struct config_group*) ; 
 struct config_group* configfs_register_default_group (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  functions_group ; 
 int /*<<< orphan*/  pci_epf_group_type ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 

struct config_group *pci_ep_cfs_add_epf_group(const char *name)
{
	struct config_group *group;

	group = configfs_register_default_group(functions_group, name,
						&pci_epf_group_type);
	if (IS_ERR(group))
		pr_err("failed to register configfs group for %s function\n",
		       name);

	return group;
}