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
 struct device_node* cvm_oct_of_get_child (struct device_node*,int) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static struct device_node *cvm_oct_node_for_port(struct device_node *pip,
						 int interface, int port)
{
	struct device_node *ni, *np;

	ni = cvm_oct_of_get_child(pip, interface);
	if (!ni)
		return NULL;

	np = cvm_oct_of_get_child(ni, port);
	of_node_put(ni);

	return np;
}