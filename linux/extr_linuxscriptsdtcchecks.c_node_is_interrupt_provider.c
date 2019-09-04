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
struct property {int dummy; } ;
struct node {int dummy; } ;

/* Variables and functions */
 struct property* get_property (struct node*,char*) ; 

__attribute__((used)) static bool node_is_interrupt_provider(struct node *node)
{
	struct property *prop;

	prop = get_property(node, "interrupt-controller");
	if (prop)
		return true;

	prop = get_property(node, "interrupt-map");
	if (prop)
		return true;

	return false;
}