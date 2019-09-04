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
typedef  scalar_t__ u64 ;
struct resource {scalar_t__ start; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 struct device_node* of_find_all_nodes (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static bool find_by_address(u64 base_address)
{
	struct device_node *dn = of_find_all_nodes(NULL);
	struct resource res;

	while (dn) {
		if (!of_address_to_resource(dn, 0, &res)) {
			if (res.start == base_address) {
				of_node_put(dn);
				return true;
			}
		}
		dn = of_find_all_nodes(dn);
	}

	return false;
}