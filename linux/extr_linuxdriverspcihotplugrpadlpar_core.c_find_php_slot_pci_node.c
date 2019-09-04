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
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* of_find_node_by_name (struct device_node*,char*) ; 
 int rpaphp_check_drc_props (struct device_node*,char*,char*) ; 

__attribute__((used)) static struct device_node *find_php_slot_pci_node(char *drc_name,
						  char *drc_type)
{
	struct device_node *np = NULL;
	int rc;

	while ((np = of_find_node_by_name(np, "pci"))) {
		rc = rpaphp_check_drc_props(np, drc_name, drc_type);
		if (rc == 0)
			break;
	}

	return np;
}