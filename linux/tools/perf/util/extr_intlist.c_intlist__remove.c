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
struct intlist {int /*<<< orphan*/  rblist; } ;
struct int_node {int /*<<< orphan*/  rb_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  rblist__remove_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void intlist__remove(struct intlist *ilist, struct int_node *node)
{
	rblist__remove_node(&ilist->rblist, &node->rb_node);
}