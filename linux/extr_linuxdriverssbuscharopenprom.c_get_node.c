#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  phandle ;
struct TYPE_3__ {struct device_node* lastnode; } ;
typedef  TYPE_1__ DATA ;

/* Variables and functions */
 struct device_node* of_find_node_by_phandle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct device_node *get_node(phandle n, DATA *data)
{
	struct device_node *dp = of_find_node_by_phandle(n);

	if (dp)
		data->lastnode = dp;

	return dp;
}