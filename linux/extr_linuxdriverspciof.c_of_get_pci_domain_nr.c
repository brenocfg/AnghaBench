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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

int of_get_pci_domain_nr(struct device_node *node)
{
	u32 domain;
	int error;

	error = of_property_read_u32(node, "linux,pci-domain", &domain);
	if (error)
		return error;

	return (u16)domain;
}