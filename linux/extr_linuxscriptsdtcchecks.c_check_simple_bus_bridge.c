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
struct node {int /*<<< orphan*/ * bus; } ;
struct dt_info {int dummy; } ;
struct check {int dummy; } ;

/* Variables and functions */
 scalar_t__ node_is_compatible (struct node*,char*) ; 
 int /*<<< orphan*/  simple_bus ; 

__attribute__((used)) static void check_simple_bus_bridge(struct check *c, struct dt_info *dti, struct node *node)
{
	if (node_is_compatible(node, "simple-bus"))
		node->bus = &simple_bus;
}