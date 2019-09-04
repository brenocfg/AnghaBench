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
struct ctl_node {struct ctl_table_header* header; } ;
struct ctl_dir {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 struct ctl_node* first_usable_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_lock ; 

__attribute__((used)) static void first_entry(struct ctl_dir *dir,
	struct ctl_table_header **phead, struct ctl_table **pentry)
{
	struct ctl_table_header *head = NULL;
	struct ctl_table *entry = NULL;
	struct ctl_node *ctl_node;

	spin_lock(&sysctl_lock);
	ctl_node = first_usable_entry(rb_first(&dir->root));
	spin_unlock(&sysctl_lock);
	if (ctl_node) {
		head = ctl_node->header;
		entry = &head->ctl_table[ctl_node - head->node];
	}
	*phead = head;
	*pentry = entry;
}