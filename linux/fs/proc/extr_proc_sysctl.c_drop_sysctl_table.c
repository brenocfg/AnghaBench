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
struct ctl_table_header {int /*<<< orphan*/  count; scalar_t__ nreg; struct ctl_dir* parent; } ;
struct ctl_dir {struct ctl_table_header header; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct ctl_table_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_links (struct ctl_table_header*) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  start_unregistering (struct ctl_table_header*) ; 

__attribute__((used)) static void drop_sysctl_table(struct ctl_table_header *header)
{
	struct ctl_dir *parent = header->parent;

	if (--header->nreg)
		return;

	if (parent) {
		put_links(header);
		start_unregistering(header);
	}

	if (!--header->count)
		kfree_rcu(header, rcu);

	if (parent)
		drop_sysctl_table(&parent->header);
}