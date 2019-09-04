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
struct device_node {int /*<<< orphan*/  full_name; struct device_node* parent; } ;

/* Variables and functions */
 char const* kbasename (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *device_node_name_for_depth(const struct device_node *np, int depth)
{
	for ( ; np && depth; depth--)
		np = np->parent;

	return kbasename(np->full_name);
}