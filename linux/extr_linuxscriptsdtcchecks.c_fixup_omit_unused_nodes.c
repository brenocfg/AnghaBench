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
struct node {int /*<<< orphan*/  is_referenced; scalar_t__ omit_if_unused; } ;
struct dt_info {int dummy; } ;
struct check {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_node (struct node*) ; 

__attribute__((used)) static void fixup_omit_unused_nodes(struct check *c, struct dt_info *dti,
				    struct node *node)
{
	if (node->omit_if_unused && !node->is_referenced)
		delete_node(node);
}