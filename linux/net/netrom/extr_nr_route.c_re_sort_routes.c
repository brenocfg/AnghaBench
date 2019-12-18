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
struct nr_node {int which; TYPE_1__* routes; } ;
struct TYPE_3__ {scalar_t__ quality; } ;

/* Variables and functions */
 int /*<<< orphan*/  swap (TYPE_1__,TYPE_1__) ; 

__attribute__((used)) static void re_sort_routes(struct nr_node *nr_node, int x, int y)
{
	if (nr_node->routes[y].quality > nr_node->routes[x].quality) {
		if (nr_node->which == x)
			nr_node->which = y;
		else if (nr_node->which == y)
			nr_node->which = x;

		swap(nr_node->routes[x], nr_node->routes[y]);
	}
}