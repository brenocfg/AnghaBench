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
typedef  int uint32_t ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int be32_to_cpup (int const*) ; 
 struct device_node* of_get_parent (struct device_node*) ; 
 int* of_get_property (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int get_parent_handle(struct device_node *np)
{
	struct device_node *parent;
	const uint32_t *prop;
	uint32_t handle;
	int len;

	parent = of_get_parent(np);
	if (!parent)
		/* It's not really possible for this to fail */
		return -ENODEV;

	/*
	 * The proper name for the handle property is "hv-handle", but some
	 * older versions of the hypervisor used "reg".
	 */
	prop = of_get_property(parent, "hv-handle", &len);
	if (!prop)
		prop = of_get_property(parent, "reg", &len);

	if (!prop || (len != sizeof(uint32_t))) {
		/* This can happen only if the node is malformed */
		of_node_put(parent);
		return -ENODEV;
	}

	handle = be32_to_cpup(prop);
	of_node_put(parent);

	return handle;
}