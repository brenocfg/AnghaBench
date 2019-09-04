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
struct resource {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int of_address_to_resource (struct device_node*,int,struct resource*) ; 
 int of_property_match_string (struct device_node*,char*,char*) ; 

__attribute__((used)) static int miphy28lp_get_resource_byname(struct device_node *child,
					  char *rname, struct resource *res)
{
	int index;

	index = of_property_match_string(child, "reg-names", rname);
	if (index < 0)
		return -ENODEV;

	return of_address_to_resource(child, index, res);
}