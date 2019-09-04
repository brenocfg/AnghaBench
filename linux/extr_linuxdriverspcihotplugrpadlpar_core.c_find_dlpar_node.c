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
 int NODE_TYPE_PHB ; 
 int NODE_TYPE_SLOT ; 
 int NODE_TYPE_VIO ; 
 struct device_node* find_php_slot_pci_node (char*,char*) ; 
 struct device_node* find_vio_slot_node (char*) ; 

__attribute__((used)) static struct device_node *find_dlpar_node(char *drc_name, int *node_type)
{
	struct device_node *dn;

	dn = find_php_slot_pci_node(drc_name, "SLOT");
	if (dn) {
		*node_type = NODE_TYPE_SLOT;
		return dn;
	}

	dn = find_php_slot_pci_node(drc_name, "PHB");
	if (dn) {
		*node_type = NODE_TYPE_PHB;
		return dn;
	}

	dn = find_vio_slot_node(drc_name);
	if (dn) {
		*node_type = NODE_TYPE_VIO;
		return dn;
	}

	return NULL;
}