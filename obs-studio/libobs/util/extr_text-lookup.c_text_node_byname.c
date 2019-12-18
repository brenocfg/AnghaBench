#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  array; } ;
struct text_node {struct text_node* next; TYPE_1__ str; struct text_node* first_subnode; } ;

/* Variables and functions */
 scalar_t__ astrcmpi_n (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct text_node *text_node_byname(struct text_node *node,
					  const char *name)
{
	struct text_node *subnode = node->first_subnode;

	while (subnode) {
		if (astrcmpi_n(subnode->str.array, name, subnode->str.len) == 0)
			return subnode;

		subnode = subnode->next;
	}

	return NULL;
}