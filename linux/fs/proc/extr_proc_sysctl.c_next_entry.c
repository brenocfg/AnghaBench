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
struct ctl_table_header {struct ctl_node* node; struct ctl_table* ctl_table; } ;
struct ctl_table {int dummy; } ;
struct ctl_node {struct ctl_table_header* header; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 struct ctl_node* first_usable_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_lock ; 
 int /*<<< orphan*/  unuse_table (struct ctl_table_header*) ; 

__attribute__((used)) static void next_entry(struct ctl_table_header **phead, struct ctl_table **pentry)
{
	struct ctl_table_header *head = *phead;
	struct ctl_table *entry = *pentry;
	struct ctl_node *ctl_node = &head->node[entry - head->ctl_table];

	spin_lock(&sysctl_lock);
	unuse_table(head);

	ctl_node = first_usable_entry(rb_next(&ctl_node->node));
	spin_unlock(&sysctl_lock);
	head = NULL;
	if (ctl_node) {
		head = ctl_node->header;
		entry = &head->ctl_table[ctl_node - head->node];
	}
	*phead = head;
	*pentry = entry;
}