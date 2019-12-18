#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rb_node {int dummy; } ;
struct ctl_table_header {TYPE_2__* parent; struct ctl_table* ctl_table; TYPE_1__* node; } ;
struct ctl_table {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  root; } ;
struct TYPE_3__ {struct rb_node node; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_erase (struct rb_node*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void erase_entry(struct ctl_table_header *head, struct ctl_table *entry)
{
	struct rb_node *node = &head->node[entry - head->ctl_table].node;

	rb_erase(node, &head->parent->root);
}